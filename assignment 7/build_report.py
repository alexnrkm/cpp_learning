import os
import shutil
import zipfile
import xml.etree.ElementTree as ET
from pathlib import Path


W_NS = "http://schemas.openxmlformats.org/wordprocessingml/2006/main"
R_NS = "http://schemas.openxmlformats.org/officeDocument/2006/relationships"
REL_NS = "http://schemas.openxmlformats.org/package/2006/relationships"
WP_NS = "http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing"
A_NS = "http://schemas.openxmlformats.org/drawingml/2006/main"
PIC_NS = "http://schemas.openxmlformats.org/drawingml/2006/picture"

NS = {
    "w": W_NS,
    "r": R_NS,
    "rel": REL_NS,
    "wp": WP_NS,
    "a": A_NS,
    "pic": PIC_NS,
}

for prefix, uri in NS.items():
    ET.register_namespace(prefix, uri)


def w_tag(name: str) -> str:
    return f"{{{W_NS}}}{name}"


def r_tag(name: str) -> str:
    return f"{{{R_NS}}}{name}"


def rel_tag(name: str) -> str:
    return f"{{{REL_NS}}}{name}"


def paragraph_text(paragraph: ET.Element) -> str:
    parts = []
    for text_node in paragraph.findall(".//w:t", NS):
        parts.append(text_node.text or "")
    return "".join(parts)


def make_run_properties(
    *,
    bold: bool = False,
    font: str = "Times New Roman",
    size_half_points: int = 24,
) -> ET.Element:
    r_pr = ET.Element(w_tag("rPr"))
    ET.SubElement(
        r_pr,
        w_tag("rFonts"),
        {
            w_tag("ascii"): font,
            w_tag("hAnsi"): font,
            w_tag("cs"): font,
        },
    )
    if bold:
        ET.SubElement(r_pr, w_tag("b"))
        ET.SubElement(r_pr, w_tag("bCs"))
    ET.SubElement(r_pr, w_tag("sz"), {w_tag("val"): str(size_half_points)})
    ET.SubElement(r_pr, w_tag("szCs"), {w_tag("val"): str(size_half_points)})
    ET.SubElement(r_pr, w_tag("lang"), {w_tag("val"): "en-US"})
    return r_pr


def make_paragraph(
    text: str = "",
    *,
    bold: bool = False,
    font: str = "Times New Roman",
    size_half_points: int = 24,
    center: bool = False,
    page_break_before: bool = False,
) -> ET.Element:
    p = ET.Element(w_tag("p"))
    p_pr = ET.SubElement(p, w_tag("pPr"))
    ET.SubElement(
        p_pr,
        w_tag("spacing"),
        {
            w_tag("before"): "100",
            w_tag("after"): "100",
            w_tag("line"): "240",
            w_tag("lineRule"): "auto",
        },
    )
    if center:
        ET.SubElement(p_pr, w_tag("jc"), {w_tag("val"): "center"})
    if page_break_before:
        ET.SubElement(p_pr, w_tag("pageBreakBefore"))

    r = ET.SubElement(p, w_tag("r"))
    r.append(make_run_properties(bold=bold, font=font, size_half_points=size_half_points))
    t = ET.SubElement(r, w_tag("t"))
    if text.startswith(" ") or text.endswith(" ") or "  " in text:
        t.set("{http://www.w3.org/XML/1998/namespace}space", "preserve")
    t.text = text
    return p


def make_code_paragraph(text: str) -> ET.Element:
    return make_paragraph(text, font="Courier New", size_half_points=18)


def png_size(path: Path) -> tuple[int, int]:
    with path.open("rb") as fh:
        data = fh.read(24)
    if data[:8] != b"\x89PNG\r\n\x1a\n":
        raise ValueError(f"{path} is not a PNG file")
    width = int.from_bytes(data[16:20], "big")
    height = int.from_bytes(data[20:24], "big")
    return width, height


def image_paragraph(rel_id: str, image_name: str, width_px: int, height_px: int, doc_pr_id: int) -> ET.Element:
    max_width_emu = 6 * 914400
    cx = width_px * 9525
    cy = height_px * 9525
    if cx > max_width_emu:
        scale = max_width_emu / cx
        cx = int(cx * scale)
        cy = int(cy * scale)

    xml = f"""
    <w:p xmlns:w="{W_NS}" xmlns:r="{R_NS}" xmlns:wp="{WP_NS}" xmlns:a="{A_NS}" xmlns:pic="{PIC_NS}">
      <w:r>
        <w:drawing>
          <wp:inline distT="0" distB="0" distL="0" distR="0">
            <wp:extent cx="{cx}" cy="{cy}"/>
            <wp:docPr id="{doc_pr_id}" name="{image_name}"/>
            <wp:cNvGraphicFramePr>
              <a:graphicFrameLocks noChangeAspect="1"/>
            </wp:cNvGraphicFramePr>
            <a:graphic>
              <a:graphicData uri="http://schemas.openxmlformats.org/drawingml/2006/picture">
                <pic:pic>
                  <pic:nvPicPr>
                    <pic:cNvPr id="0" name="{image_name}"/>
                    <pic:cNvPicPr/>
                  </pic:nvPicPr>
                  <pic:blipFill>
                    <a:blip r:embed="{rel_id}"/>
                    <a:stretch>
                      <a:fillRect/>
                    </a:stretch>
                  </pic:blipFill>
                  <pic:spPr>
                    <a:xfrm>
                      <a:off x="0" y="0"/>
                      <a:ext cx="{cx}" cy="{cy}"/>
                    </a:xfrm>
                    <a:prstGeom prst="rect">
                      <a:avLst/>
                    </a:prstGeom>
                  </pic:spPr>
                </pic:pic>
              </a:graphicData>
            </a:graphic>
          </wp:inline>
        </w:drawing>
      </w:r>
    </w:p>
    """
    return ET.fromstring(xml)


def main() -> None:
    base_dir = Path(r"c:\Data Structures\assignment 7")
    extract_dir = base_dir / "docx_extract"
    document_xml = extract_dir / "word" / "document.xml"
    rels_xml = extract_dir / "word" / "_rels" / "document.xml.rels"
    media_dir = extract_dir / "word" / "media"
    screenshots_dir = base_dir / "screenshots"
    output_docx = base_dir / "ADS Assignment-7 Hash Table completed.docx"

    doc_tree = ET.parse(document_xml)
    doc_root = doc_tree.getroot()
    body = doc_root.find("w:body", NS)
    if body is None:
        raise RuntimeError("document body not found")

    # Replace the student placeholder line.
    for paragraph in body.findall("w:p", NS):
        text = paragraph_text(paragraph)
        if "Student (Last Name, First Name)" in text:
            text_nodes = paragraph.findall(".//w:t", NS)
            if text_nodes:
                text_nodes[-1].text = ": Pocz, Bartosz"
            break

    rels_tree = ET.parse(rels_xml)
    rels_root = rels_tree.getroot()

    existing_rel_ids = []
    for rel in rels_root.findall("rel:Relationship", NS):
        rel_id = rel.get("Id", "")
        if rel_id.startswith("rId") and rel_id[3:].isdigit():
            existing_rel_ids.append(int(rel_id[3:]))

    next_rel_num = max(existing_rel_ids, default=0) + 1
    next_image_num = 1
    for item in media_dir.glob("image*.png"):
        name = item.stem.replace("image", "")
        if name.isdigit():
            next_image_num = max(next_image_num, int(name) + 1)

    sect_pr = body.find("w:sectPr", NS)
    insert_index = len(body) - 1 if sect_pr is not None else len(body)

    body.insert(insert_index, make_paragraph("Completed Solutions", bold=True, size_half_points=28, center=True, page_break_before=True))
    insert_index += 1

    doc_pr_id = 1000
    for ex_num in range(1, 16):
        code_path = base_dir / f"ex{ex_num}.cpp"
        screenshot_path = screenshots_dir / f"ex{ex_num}.png"
        if not code_path.exists():
            raise FileNotFoundError(code_path)
        if not screenshot_path.exists():
            raise FileNotFoundError(screenshot_path)

        body.insert(insert_index, make_paragraph(f"Exercise {ex_num}", bold=True, size_half_points=26))
        insert_index += 1
        body.insert(insert_index, make_paragraph(f"Code (ex{ex_num}.cpp):", bold=True))
        insert_index += 1

        code_lines = code_path.read_text(encoding="utf-8").splitlines()
        for line in code_lines:
            body.insert(insert_index, make_code_paragraph(line))
            insert_index += 1

        body.insert(insert_index, make_paragraph("Screenshot:", bold=True))
        insert_index += 1

        rel_id = f"rId{next_rel_num}"
        next_rel_num += 1
        image_name = f"image{next_image_num}.png"
        next_image_num += 1
        shutil.copyfile(screenshot_path, media_dir / image_name)
        ET.SubElement(
            rels_root,
            rel_tag("Relationship"),
            {
                "Id": rel_id,
                "Type": "http://schemas.openxmlformats.org/officeDocument/2006/relationships/image",
                "Target": f"media/{image_name}",
            },
        )

        width_px, height_px = png_size(screenshot_path)
        body.insert(insert_index, image_paragraph(rel_id, image_name, width_px, height_px, doc_pr_id))
        insert_index += 1
        doc_pr_id += 1

    doc_tree.write(document_xml, encoding="UTF-8", xml_declaration=True)
    rels_tree.write(rels_xml, encoding="UTF-8", xml_declaration=True)

    if output_docx.exists():
        output_docx.unlink()

    zip_temp = output_docx.with_suffix(".zip")
    if zip_temp.exists():
        zip_temp.unlink()

    with zipfile.ZipFile(zip_temp, "w", zipfile.ZIP_DEFLATED) as zf:
        for path in extract_dir.rglob("*"):
            if path.is_file():
                arcname = path.relative_to(extract_dir).as_posix()
                info = zipfile.ZipInfo(arcname)
                info.compress_type = zipfile.ZIP_DEFLATED
                info.date_time = (2026, 3, 9, 0, 0, 0)
                zf.writestr(info, path.read_bytes())

    zip_temp.rename(output_docx)
    print(output_docx)


if __name__ == "__main__":
    main()
