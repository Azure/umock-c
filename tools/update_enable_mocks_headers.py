#!/usr/bin/env python3
"""Stub script kept for backward compatibility.

This repository now uses a PowerShell workflow for updating ENABLE_MOCKS
sections. Please invoke ``tools/update_enable_mocks_headers.ps1`` instead.
"""

import sys


def main() -> int:
    message = (
        "tools/update_enable_mocks_headers.py has been replaced. "
        "Run powershell -ExecutionPolicy Bypass -File "
        "tools/update_enable_mocks_headers.ps1 instead."
    )
    print(message, file=sys.stderr)
    return 1


if __name__ == "__main__":
    sys.exit(main())
