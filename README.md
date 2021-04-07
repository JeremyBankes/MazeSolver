# MazeSolver
### Solves a maze using a custom stack implementation, and visualizes it using the Win32 console API.

---

[Download Binary](https://github.com/JeremyBankes/MazeSolver/releases/download/1.0.0/MazeSolver.zip) (MazeSolver.zip)

This binary was built using MinGW64 for a Windows machine.

---

![Cover Image](https://github.com/JeremyBankes/MazeSolver/raw/main/cover.png)

---

This project takes a OOP approach to solving a maze using a custom data structure. In this case, a [stack](https://en.wikipedia.org/wiki/Stack_(abstract_data_type)). A stack is considered a LIFO data structure (last in, first out), essentially meaning anything you add to a stack will have to be removed before anything below it; I like to think of a stack of plates. My implementation of this stack is built onto from a previous implementation of a [linked list](https://en.wikipedia.org/wiki/Linked_list).

For the visualization, although I enjoy graphics programming, I wanted something quick and light weight to run and develop. So I opt for the [Win32 console API](https://docs.microsoft.com/en-us/windows/console/using-the-console). By setting the console's font to be a square raster font, you can quick and easily manipulate what looks like tiles.