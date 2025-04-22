# Y8 JavaScript Engine

> **Note**: This project is currently under active development and is proprietary.  
> Public usage, distribution, or contribution is not permitted until the first official release.

---

## Overview

**Y8** is a custom-built, high-performance JavaScript engine inspired by Google’s [V8](https://v8.dev).  
It introduces native multithreaded execution into the JavaScript runtime while maintaining ECMAScript compliance.  
The architecture is designed to be modular, context-aware, and scalable for modern application demands.

---

## Core Features

- **Multithreaded Execution**  
  Native support for parallel JavaScript execution using in-code directives such as `//@multithreading`.

- **Context-Aware Analysis**  
  Maintains consistent lexical and execution context across threads, preventing race conditions and state leakage.

- **Modular Architecture**  
  Components (lexer, parser, interpreter) are designed independently for ease of maintenance, testing, and reuse.

- **Thread Safety and Synchronization**  
  All multithreaded processes use synchronization primitives to ensure deterministic, race-free execution.

- **Verbose Debugging and Unicode Support**  
  Built-in debugging utilities, Unicode character recognition, and detailed error handling included in the lexer.

---

## Design Principles

- **Opt-In Multithreading**  
  Multithreading is activated only when explicitly enabled using `//@multithreading`, ensuring compatibility and control.

- **Separation of Concerns**  
  Lexer, parser, and interpreter operate as independent layers with minimal interdependency.

- **Performance Without Compromise**  
  Focused on high throughput with strict adherence to JavaScript semantics and thread safety.

- **Extensible Foundation**  
  Built with future support for features such as JIT compilation, advanced optimization, and newer ECMAScript proposals.

---

## Current Status

- Single-threaded lexer implemented
- Support for `lexemeTypes` and expanded token definitions
- Multithreaded lexer architecture under development
- Parser and interpreter scaffolding in progress

---

## Usage Notes

- By default, the lexer executes in **single-threaded** mode.  
  Add `//@multithreading` at the top of a script to enable multithreaded execution.

- Tokenization is **context-sensitive** and supports ECMAScript edge cases and Unicode input.

- All major components are built with debugging, profiling, and verbose logging modes.

---

## Contributions

This is currently a **solo development project**.  
Contribution opportunities will be evaluated after the first public release.

Planned documentation for contributors includes:

- Architectural overview  
- API documentation  
- Development and testing guidelines  
- Contribution and code review processes

---

## License

This project is **not yet licensed** and remains **proprietary**.  
License terms will be announced upon the first stable release.

---

## Recent Updates

**January 29, 2025**  
- Added support for `lexemeTypes`  
- Introduced extended token classification for parser compatibility

---
