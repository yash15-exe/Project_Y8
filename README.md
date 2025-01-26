# Y8 Project - A Multithreaded execution engine for javascript.
### This project is proprietary and not open for public use or distribution.

## Overview
Y8 is a custom-built JavaScript engine inspired by the V8 engine, designed to support both single-threaded and multithreaded JavaScript execution. This project aims to achieve ECMAScript compliance while incorporating modern features like:

- Multithreaded lexer and parser (based on directives like `//@multithreading`).
- Native multithreaded JavaScript execution.
- Modular and optimized architecture.
- This program emphasizes on creating a multithreaded execution environment while maintaining thread safety and context awareness.


### **Phase 1: Planning & Understanding (January 1 - January 10)**
- **Status**: Ongoing
- **Goals:**
  - Understand the V8 engine's architecture and functionality.
  - Create a roadmap for the entire Y8 engine.
  - Brush up on C++ for implementation readiness.

### **Phase 2: Lexer Implementation (January 10th - January 30th)**
- **Goals:**
  - Design a multithreaded lexer using finite state automata (FSA).
  - Add features such as Unicode support, detailed error handling, and context-sensitive analysis.
  - Include a verbose mode for debugging and performance optimizations.

### **Future Phases**
1. **Parser**: Design and implement a parser for syntax analysis.
2. **Interpreter**: Develop the core interpreter for executing JavaScript.
3. **Control Flow**: Implement control flow mechanisms (e.g., loops, conditions).
4. **Error Handling**: Introduce comprehensive error handling.
5. **Testing & Debugging**: Perform rigorous testing and debugging to ensure reliability.

## Notes
- The lexer will default to single threaded mode unless overridden by a directive.
- Aim for modularity and reusability in all components.
- Document decisions and challenges for inclusion in full documentation later.

## Contributions
Currently, this project is a solo endeavor, but collaboration opportunities might open later. Documentation will be expanded to facilitate contributions.

## Roadmap
- [ ] Finalize the architecture and design document.
- [ ] Implement the lexer.
- [ ] Begin working on the parser.
- [ ] Integrate all components for the interpreter.
- [ ] Optimize for multithreading and performance.

## References
- ECMAScript standards documentation.
- V8 engine architecture resources.
- C++ multithreading tutorials.

## License
This project is under development and not yet licensed. License information will be updated in the full documentation.
