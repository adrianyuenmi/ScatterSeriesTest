# ScatterSeriesTest

This project aims to demonstrate how `QChart` when used in a background thread crashes the application.

[REG 5.14.2 -> 5.15.2] Regression: worked on `5.14.2`, crashes on `5.15.2`.

Compiler: `Microsoft Visual C++ Compiler 16.8.31019.35 (amd64)`

OS: `Microsoft Windows 10 Pro 64-bit (version 10.0.18363 Build 18363)`

# Use case

I want to generate a `QImage` of a line chart in a **worker thread**.
`QChartView` cannot be employed in my case as `QWidget`s cannot be created in non-GUI threads.

The current implementation is somewhat convoluted. The `QChart` has to be attached to a `QGraphicsScene`,
which is then rendered by a QPainter attached to the output `QImage`.

If there is a more straight-forward, and less error-prone, way to do this, please let me know.

# Bug Reproduction

- Build and run the application in Debug mode
- Press the top button "Generate In-Range" to generate a QChart which is displayed.
- Repeatedly pressing the top button did not generate any bugs. Application behaviour is normal.
- Press the bottom button "Generate Out-of-Range", a(n incorrectly renderred) graph is displayed
- Repeatedly pressing should cause a crash with the below message.

> "ASSERT failure in QCoreApplication::sendEvent: "Cannot send events to objects owned by a different thread. Current thread 0x0x1d488bbcb40. Receiver '' (of type 'QTextDocument') was created in thread 0x0x1d48646c120", file kernel\qcoreapplication.cpp, line 558
> Debug Error!"

# Secondary Bug Highlight

Why does the graph render weirdly when a value is out of the axis range?
