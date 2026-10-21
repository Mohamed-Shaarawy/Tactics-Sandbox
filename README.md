# Tactics-Sandbox

[![CI](https://github.com/Mohamed-Shaarawy/Tactics-Sandbox/actions/workflows/ci.yml/badge.svg)](https://github.com/Mohamed-Shaarawy/Tactics-Sandbox/actions/workflows/ci.yml)

A turn-based tactical RPG combat sandbox. All game rules live in **TacticsCore**, an engine-agnostic C++20 library built test-first. **Unreal Engine 5** is only the front end: it sends commands to the core and presents the events the core emits.

Personal project, started October 2026. **Status:** early setup.

## Layout

| Folder | What it is |
|---|---|
| `TacticsCore/` | Plain C++20 library (CMake, GoogleTest). No Unreal headers. |
| `TacticsUE/` | Unreal Engine 5 front end *(coming soon)* |

## Build and test the core

No Unreal Engine needed. Requires CMake 3.24+ and a C++20 compiler (MSVC, Clang or GCC).

```sh
cmake -S TacticsCore -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

GoogleTest is downloaded automatically during the first configure.

To run with sanitizers like CI does, add `-DTACTICS_SANITIZE=address` (MSVC) or `-DTACTICS_SANITIZE=address,undefined` (Clang/GCC) to the first command.

## Planned

- Entity-component system
- Grid pathfinding (A\*, movement range)
- d20 combat rules (attack rolls, advantage, saving throws, status effects)
- Utility AI for enemy turns
- Systemic surfaces (fire, oil, water, lightning)
- Abilities defined in Lua
