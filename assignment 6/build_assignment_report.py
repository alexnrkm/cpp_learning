import copy
import os
import struct
import zipfile
import xml.etree.ElementTree as ET


NS = {
    "a": "http://schemas.openxmlformats.org/drawingml/2006/main",
    "pic": "http://schemas.openxmlformats.org/drawingml/2006/picture",
    "r": "http://schemas.openxmlformats.org/officeDocument/2006/relationships",
    "rel": "http://schemas.openxmlformats.org/package/2006/relationships",
    "w": "http://schemas.openxmlformats.org/wordprocessingml/2006/main",
    "wp": "http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing",
}

for prefix, uri in NS.items():
    ET.register_namespace(prefix, uri)

ET.register_namespace("w14", "http://schemas.microsoft.com/office/word/2010/wordml")
ET.register_namespace("mc", "http://schemas.openxmlformats.org/markup-compatibility/2006")


TEMPLATE_PATH = r"C:\Users\bpocz\Downloads\ADS Assignment-6 Recursion and Backtracking.docx"
OUTPUT_PATH = r"C:\Data Structures\assignment 6\ADS Assignment-6 Recursion and Backtracking - Alexandr Kim.docx"
CODE_DIR = r"C:\Data Structures\assignment 6"
SCREENSHOT_DIR = r"C:\Data Structures\assignment 6\desktop-screenshots"

W_NS = "{%s}" % NS["w"]
R_NS = "{%s}" % NS["r"]
REL_NS = "{%s}" % NS["rel"]


def qn(prefix: str, tag: str) -> str:
    return "{%s}%s" % (NS[prefix], tag)


def png_size(path: str) -> tuple[int, int]:
    with open(path, "rb") as f:
        signature = f.read(8)
        if signature != b"\x89PNG\r\n\x1a\n":
            raise ValueError(f"Unsupported image format: {path}")
        length = struct.unpack(">I", f.read(4))[0]
        chunk_type = f.read(4)
        if chunk_type != b"IHDR" or length < 8:
            raise ValueError(f"Invalid PNG header: {path}")
        width, height = struct.unpack(">II", f.read(8))
    return width, height


def set_paragraph_text(paragraph, text: str, font_size: int = 24, bold: bool = False, mono: bool = False):
    for child in list(paragraph):
        paragraph.remove(child)

    p_pr = ET.SubElement(paragraph, qn("w", "pPr"))
    ET.SubElement(p_pr, qn("w", "spacing"), {qn("w", "before"): "60", qn("w", "after"): "60"})

    run = ET.SubElement(paragraph, qn("w", "r"))
    r_pr = ET.SubElement(run, qn("w", "rPr"))
    font_name = "Courier New" if mono else "Times New Roman"
    ET.SubElement(
        r_pr,
        qn("w", "rFonts"),
        {
            qn("w", "ascii"): font_name,
            qn("w", "hAnsi"): font_name,
            qn("w", "cs"): font_name,
            qn("w", "eastAsia"): font_name,
        },
    )
    if bold:
        ET.SubElement(r_pr, qn("w", "b"))
        ET.SubElement(r_pr, qn("w", "bCs"))
    ET.SubElement(r_pr, qn("w", "sz"), {qn("w", "val"): str(font_size)})
    ET.SubElement(r_pr, qn("w", "szCs"), {qn("w", "val"): str(font_size)})

    t = ET.SubElement(run, qn("w", "t"))
    if text.startswith(" ") or text.endswith(" ") or "  " in text:
        t.set("{http://www.w3.org/XML/1998/namespace}space", "preserve")
    t.text = text


def make_paragraph(text: str, font_size: int = 24, bold: bool = False, mono: bool = False):
    p = ET.Element(qn("w", "p"))
    set_paragraph_text(p, text, font_size=font_size, bold=bold, mono=mono)
    return p


def make_blank_paragraph():
    p = ET.Element(qn("w", "p"))
    p_pr = ET.SubElement(p, qn("w", "pPr"))
    ET.SubElement(p_pr, qn("w", "spacing"), {qn("w", "before"): "20", qn("w", "after"): "20"})
    ET.SubElement(ET.SubElement(p, qn("w", "r")), qn("w", "br"))
    return p


def make_image_paragraph(rel_id: str, image_name: str, width_px: int, height_px: int, doc_pr_id: int):
    max_width_emu = 5_200_000
    width_emu = min(max_width_emu, int(width_px * 9525))
    height_emu = int(height_px * (width_emu / width_px))

    p = ET.Element(qn("w", "p"))
    p_pr = ET.SubElement(p, qn("w", "pPr"))
    ET.SubElement(p_pr, qn("w", "spacing"), {qn("w", "before"): "60", qn("w", "after"): "120"})

    run = ET.SubElement(p, qn("w", "r"))
    drawing = ET.SubElement(run, qn("w", "drawing"))
    inline = ET.SubElement(
        drawing,
        qn("wp", "inline"),
        {"distT": "0", "distB": "0", "distL": "0", "distR": "0"},
    )
    ET.SubElement(inline, qn("wp", "extent"), {"cx": str(width_emu), "cy": str(height_emu)})
    ET.SubElement(inline, qn("wp", "effectExtent"), {"l": "0", "t": "0", "r": "0", "b": "0"})
    ET.SubElement(inline, qn("wp", "docPr"), {"id": str(doc_pr_id), "name": image_name})
    ET.SubElement(inline, qn("wp", "cNvGraphicFramePr"))

    graphic = ET.SubElement(inline, qn("a", "graphic"))
    graphic_data = ET.SubElement(
        graphic,
        qn("a", "graphicData"),
        {"uri": "http://schemas.openxmlformats.org/drawingml/2006/picture"},
    )
    pic = ET.SubElement(graphic_data, qn("pic", "pic"))
    nv_pic_pr = ET.SubElement(pic, qn("pic", "nvPicPr"))
    ET.SubElement(nv_pic_pr, qn("pic", "cNvPr"), {"id": "0", "name": image_name})
    ET.SubElement(nv_pic_pr, qn("pic", "cNvPicPr"))

    blip_fill = ET.SubElement(pic, qn("pic", "blipFill"))
    ET.SubElement(blip_fill, qn("a", "blip"), {qn("r", "embed"): rel_id})
    stretch = ET.SubElement(blip_fill, qn("a", "stretch"))
    ET.SubElement(stretch, qn("a", "fillRect"))

    sp_pr = ET.SubElement(pic, qn("pic", "spPr"))
    xfrm = ET.SubElement(sp_pr, qn("a", "xfrm"))
    ET.SubElement(xfrm, qn("a", "off"), {"x": "0", "y": "0"})
    ET.SubElement(xfrm, qn("a", "ext"), {"cx": str(width_emu), "cy": str(height_emu)})
    prst = ET.SubElement(sp_pr, qn("a", "prstGeom"), {"prst": "rect"})
    ET.SubElement(prst, qn("a", "avLst"))
    return p


def get_cell_text(cell) -> str:
    parts = []
    for t in cell.findall(".//w:t", NS):
        if t.text:
            parts.append(t.text)
    return "".join(parts).strip()


with zipfile.ZipFile(TEMPLATE_PATH, "r") as zin:
    document_tree = ET.fromstring(zin.read("word/document.xml"))
    rels_tree = ET.fromstring(zin.read("word/_rels/document.xml.rels"))
    original_entries = {name: zin.read(name) for name in zin.namelist()}

body = document_tree.find(qn("w", "body"))
tables = body.findall(qn("w", "tbl"))

student_updated = False
for paragraph in body.findall(qn("w", "p")):
    text = "".join(t.text or "" for t in paragraph.findall(".//w:t", NS))
    if "Student (Last Name, First Name)" in text:
        set_paragraph_text(paragraph, "Student (Last Name, First Name): Alexandr Kim", font_size=27, bold=True)
        student_updated = True
        break

if not student_updated:
    raise RuntimeError("Student paragraph not found in template.")

existing_rel_ids = []
for rel in rels_tree.findall(qn("rel", "Relationship")):
    rel_id = rel.get("Id", "")
    if rel_id.startswith("rId") and rel_id[3:].isdigit():
        existing_rel_ids.append(int(rel_id[3:]))

next_rel_id = max(existing_rel_ids) + 1
next_doc_pr_id = 100
new_media = {}

exercise_index = 1
for table in tables:
    rows = table.findall(qn("w", "tr"))
    for row in rows[1:]:
        cells = row.findall(qn("w", "tc"))
        if len(cells) < 2:
            continue

        number_text = get_cell_text(cells[0])
        if not number_text.isdigit():
            continue

        code_path = os.path.join(CODE_DIR, f"ex{exercise_index}.cpp")
        image_path = os.path.join(SCREENSHOT_DIR, f"ex{exercise_index}.png")
        if not os.path.exists(code_path):
            raise FileNotFoundError(code_path)
        if not os.path.exists(image_path):
            raise FileNotFoundError(image_path)

        with open(code_path, "r", encoding="utf-8") as f:
            code_lines = f.read().splitlines()

        tc = cells[1]
        tc.append(make_blank_paragraph())
        tc.append(make_paragraph(f"Code (ex{exercise_index}.cpp):", font_size=22, bold=True))
        for line in code_lines:
            tc.append(make_paragraph(line if line else " ", font_size=18, mono=True))

        tc.append(make_blank_paragraph())
        tc.append(make_paragraph("Screenshot:", font_size=22, bold=True))

        rel_id = f"rId{next_rel_id}"
        next_rel_id += 1
        media_name = f"image_ex{exercise_index}.png"
        new_media[f"word/media/{media_name}"] = open(image_path, "rb").read()

        rels_tree.append(
            ET.Element(
                qn("rel", "Relationship"),
                {
                    "Id": rel_id,
                    "Type": "http://schemas.openxmlformats.org/officeDocument/2006/relationships/image",
                    "Target": f"media/{media_name}",
                },
            )
        )

        width_px, height_px = png_size(image_path)
        tc.append(make_image_paragraph(rel_id, media_name, width_px, height_px, next_doc_pr_id))
        next_doc_pr_id += 1
        exercise_index += 1

if exercise_index != 31:
    raise RuntimeError(f"Expected 30 exercises, processed {exercise_index - 1}.")

document_xml = ET.tostring(document_tree, encoding="utf-8", xml_declaration=True)
rels_xml = ET.tostring(rels_tree, encoding="utf-8", xml_declaration=True)

with zipfile.ZipFile(OUTPUT_PATH, "w", zipfile.ZIP_DEFLATED) as zout:
    for name, data in original_entries.items():
        if name == "word/document.xml":
            zout.writestr(name, document_xml)
        elif name == "word/_rels/document.xml.rels":
            zout.writestr(name, rels_xml)
        else:
            zout.writestr(name, data)

    for name, data in new_media.items():
        zout.writestr(name, data)

print(OUTPUT_PATH)
