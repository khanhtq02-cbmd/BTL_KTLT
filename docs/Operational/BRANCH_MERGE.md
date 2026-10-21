# Branch merge record — 2026-10-21

## DucAnh into `main`

- Merge commit: `cf10f0c` (`Merge DucAnh branch excluding repository README`).
- Base: local `main` was first reconciled with `origin/main` in `0e40d49`.
- Root `README.md` was retained from `origin/main`; DucAnh's root README update was intentionally excluded.
- Member profiles under `members/*/README.md` were retained from the integrated DucAnh tree.
- `data/CacGoiCuoc.txt` kept DucAnh's pipe-delimited six-field records because `GoiCuoc::fromFileString()` parses that format.
- Existing unrelated edits were preserved and remain unstaged: the LibreOffice lock-file deletion and `src/lib/models/imei.h` modification.

## Verification

```text
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j2
ctest --test-dir build --output-on-failure
anti-cheat-enforcer --diff --require-tests
graphify update .
```

All three CTest targets passed; the anti-cheat gate passed with zero strikes; graphify rebuilt 853 nodes and 1,809 edges. The merge was not pushed.
