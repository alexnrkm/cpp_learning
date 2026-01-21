# cpp_learning
This is a repository for my university couse Data Structures and Algorithms where i will be uploading all the excercises to track my learning process.

Sometimes when you try to push your local files to GitHub, you may get a conflict. This usually happens because your local folder and the remote repository have completely different content or were started independently. For example, the repository on GitHub might already have a `README.md` or other files, while your local folder has your own files.

You cannot just push because Git will refuse to overwrite the remote changes. You also cannot just pull normally because Git will see that the histories of the two repositories are unrelated and stop you from merging.

To fix this, you can use:

```
git pull origin main --allow-unrelated-histories
```

This command allows Git to combine the remote files with your local files, even if the two histories are completely separate. After resolving any conflicts, you can push your changes normally.
