# Plan
Key facts (so we’re aligned)

* Company wants: **C++, CV on edge, DSA, Linux, Qt/QML**.
* Time available: **\~8 weeks**.
* Deliverable target: **One solid demo repo** (Detector-GUI) that proves all five skills + README + 90–120s demo video + one-page summary.
* Work rhythm: daily commits, weekly public progress notes.

Top-level milestones (what converts into an offer)

1. Week 3: Working C++ + OpenCV webcam + DNN inference (MobileNet-SSD or tiny YOLO) on your laptop (Ubuntu/WSL). ([OpenCV Documentation][1])
2. Week 6: Qt/QML GUI showing camera feed + live bounding boxes and detection counts. ([Medium][2])
3. Week 7: Performance tuning + Linux scripts + demo video + README. ([LearnOpenCV][3])
4. Week 8: Final polishing, interview prep, DSA sharpening, and ready-to-demo repo.

Resources (read these when the week tells you)

* OpenCV DNN guide (deep dive): LearnOpenCV — essential for DNN on CPU/edge. ([LearnOpenCV][3])
* OpenCV DNN API docs (blobFromImage, readNet etc.). ([OpenCV Documentation][1])
* MobileNet-SSD repo / weights (pretrained Caffe model). ([GitHub][4])
* YOLO & OpenCV DNN guide — if you choose YOLO variant later. ([OpenCV Documentation][5])
* Learn C++ (learncpp.com) — daily reading + exercises. ([learncpp.com][6])
* Qt + QML + OpenCV integration articles & examples. ([Medium][2])

Repository & naming rules (do this first)

* Create repo: `github.com/<you>/Detector-GUI` (public).
* Branching: use `main` for stable; `dev` for daily work. Commit messages: `week1: webcam capture — commit message`.
* Keep issues / TODOs in repo — use GitHub Issues to show planning.
* Must files at root:

  * `README.md` (see template below)
  * `demo.mp4` (90–120s)
  * `src/` (C++ code + Qt project)
  * `models/` (downloaded model files with links, NOT large binaries if possible)
  * `scripts/run.sh` to build and run (easy for them to test).
  * `docs/onepager.pdf`

If you can’t put heavy models on GitHub, provide exact download commands in README.

Environment setup (run these today)

* Use Ubuntu (20.04/22.04). If on Windows, use WSL2 with Ubuntu or dual boot. If you have access to Jetson later, that’s bonus.
* Install required packages (Ubuntu):

```bash
sudo apt update
sudo apt install -y build-essential cmake git pkg-config libgtk-3-dev libopencv-dev qtcreator qt5-default
```

* Install OpenCV dev if not available; `libopencv-dev` is fine for now. If you need a newer OpenCV, build from source later.
* Install QtCreator and Qt5 dev packages.

Hard 8-week plan
(Every week: commit daily, push progress, and write one short weekly note in README under `progress/Week-N.md`.)

WEEK 0 — PREP (1–2 days, immediate)
Goal: repo created, environment installed, plan copy in README, basic git habit established.
Must produce:

* `Detector-GUI` repo with `README.md` skeleton and `progress/Week-0.md`.
* Ubuntu + toolchain installed, QtCreator runs.
  Actions:
* Create GitHub repo and push an initial README with the plan summary (copy mine later).
* Run `gcc --version`, `cmake --version`, `opencv_version` (or `pkg-config --modversion opencv4`) and save outputs in README.
* Install VS Code / Qt Creator.

WEEK 1 — C++ basics + Linux daily workflow (Days 1–7)
Goal: Get comfortable with modern C++ syntax and basic Linux dev flow; produce webcam capture demo.
Daily target: 3–4 hours learning + 1 practical task. Commit each day.
What to learn:

* LearnCpp chapters: basics, control, functions, arrays, vectors, strings. (Do \~30–40 pages.) ([learncpp.com][6])
* Linux basics: file ops, `ssh`, `scp`, `chmod`, `top`, `htop`.
  Practical tasks:
* Write and compile a C++ `webcam.cpp` using OpenCV to capture camera and show frames. (Simple loop; ESC to exit.)
* Create CMakeLists.txt to build it.
  Commands to run:

```bash
mkdir Detector-GUI && cd Detector-GUI
git init
mkdir src build
# write webcam.cpp into src/
cd build
cmake ..
make
./webcam_app
```

Deliverable by Day 7:

* `src/webcam.cpp`, `CMakeLists.txt`, `README` entry “week1 — webcam works”. Commit.

WEEK 2 — STL, modern C++ features & small projects (Days 8–14)
Goal: Gain fluency with STL containers, file I/O, smart pointers, and basic unit of concurrency.
Daily target: 3–4 hours practice, 1 hour reading.
What to learn:

* `std::vector`, `std::deque`, `std::unordered_map`, `std::priority_queue`, iterators, algorithms (`sort`, `find`, `accumulate`).
* Smart pointers (`unique_ptr`, `shared_ptr`) basics.
* Lambda functions and `std::thread` basics (if comfortable).
  Practical tasks:
* Implement small utilities: `topk.cpp` (top-k using heap), `sliding_window.cpp` (deque smoothing).
* Integrate sliding-window smoothing function with webcam app: count detected labels over last N frames (for now fake labels).
  Deliverable:
* `src/algorithms/` with 4 programs + improved `webcam` with `sliding_window` stub.

WEEK 3 — OpenCV DNN (C++) — First detection pipeline (Days 15–21)
Goal: Load a pretrained MobileNet-SSD (or tiny YOLO) and run inference in C++. Draw boxes.
Must read: OpenCV DNN docs and LearnOpenCV DNN guide. ([OpenCV Documentation][1])
Tasks:

* Download MobileNet-SSD prototxt + caffemodel or a YOLO ONNX variant:

  * MobileNet example repo: chuanqi305/MobileNet-SSD. ([GitHub][4])
* Write `dnn_detect.cpp`:

  * Use `cv::dnn::readNetFromCaffe` (or `readNetFromONNX`), `blobFromImage`, `net.setInput`, `net.forward`.
  * Parse detection output, apply confidence threshold (e.g., 0.5).
  * Draw boxes and labels.
* Build and test. Make it stable at \~5–15 FPS depending on model and laptop. If too slow, reduce input size (300×300).
  Commands / notes:
* Preprocessing matters: `blobFromImage(frame, scalefactor, Size(300,300), Scalar(127.5,127.5,127.5), true, false)`.
* If using YOLO ONNX, follow OpenCV YOLO guide for postprocessing. ([OpenCV Documentation][5])
  Deliverable:
* `src/dnn_detect.cpp`, instructions in README to download model weights, sample command lines.

WEEK 4 — DSA focus + integrate detection smoothing (Days 22–28)
Goal: Solidify DSA basics and integrate efficient data structures into pipeline.
Daily target: 1.5–2 hours DSA practice + 2–3 hours coding.
What to study:

* Arrays, strings, hashmaps, sorting, two pointers, sliding window problems. Solve 4–6 problems on GeeksforGeeks/LeetCode (easy/medium).
* Practice writing solutions in C++ and explain time/space complexity.
  Integration tasks:
* Use `std::deque` + `std::unordered_map` to keep sliding window of detections and compute top-3 objects.
* Add a module `analytics.cpp` that takes detections and outputs counts/alerts e.g., "object persistent for > 2s".
  Deliverable:
* `src/analytics.cpp` + tests + `examples/` showing output logs.

WEEK 5 — Qt & QML basics, show images (Days 29–35)
Goal: Build a minimal Qt application that displays camera frames (no detector yet).
Must read: Qt + QML image provider articles / examples. ([Medium][2])
Tasks:

* Learn Qt Creator basics, QML file structure, and how to create `QImage` from `cv::Mat`.
* Create a Qt Quick Application with a `Image` element updated from C++ via `QQuickImageProvider` or exposing `QImage` via `QVariant`.
* Ensure camera feed from OpenCV is visible in QML UI.
  Important: Do **not** block GUI thread — use `QThread` or `QtConcurrent`.
  Deliverable:
* `src/qt/` project: `detector_qt` showing live camera feed in QML.

WEEK 6 — Hook detector into Qt GUI + concurrency (Days 36–42)
Goal: Full integration — run DNN in worker thread, UI shows boxes, top-3 list updates.
Tasks:

* Move DNN inference into a worker thread, pass detection results to main thread via signals/slots.
* Convert detected boxes into QML overlay: either draw rectangles in QML Canvas or paint in C++ and send image.
* Add simple control buttons in UI: start/stop, confidence threshold slider, FPS display.
  Deliverable:
* `detector_gui` working: live feed + bounding boxes + detection list + FPS indicator. Record a 60s demo GIF.

WEEK 7 — Optimization, packaging, Linux readiness (Days 43–49)
Goal: Tune performance and make app easy to run on any Linux machine. Add scripts.
Tasks:

* Use `net.setPreferableBackend` and `setPreferableTarget` to pick best CPU backend. Test options (default, OpenVINO if available). ([LearnOpenCV][3])
* Reduce input size or frame skip to achieve stable FPS (aim 7–15 FPS).
* Add `scripts/build_and_run.sh` that builds and runs app automatically. Example:

```bash
#!/bin/bash
mkdir -p build && cd build
cmake ..
make -j4
./detector_gui
```

* Add systemd service or simple bash script to start app on boot (optional).
  Deliverable:
* `scripts/` with run scripts, `docs/performance.md` with tuning notes, `demo.mp4`.

WEEK 8 — Polish, docs, interview prep, mock demo (Days 50–56)
Goal: Final repo polish and interview prep.
Tasks:

* Final README: explanation, model download commands, run instructions, troubleshooting, sample outputs.
* One-page PDF: short tech choices, what you learned, known limitations, next steps.
* Create `demo.mp4` (90–120s): show camera, boxes, top-3 counts, code briefly, and say “I’m ready to demo live”.
* Interview prep:

  * Rehearse 3-minute explanation of architecture.
  * Prepare to answer: why C++? why Qt? why this model? how to reduce latency? memory ownership in C++? data structures used and why?
  * Practice 10 DSA problems (easy→medium) in C++ (timed).
    Deliverable:
* A polished repo with demo + one-pager + `scripts/test_run.sh`.

Daily micro plan (what to do every day)

* **Morning (optional)**: 30–60 min DSA practice (1 LeetCode easy/medium).
* **Core session (2–3 hours)**: follow weekly technical tasks. Code, test, debug. Commit.
* **Evening (1–2 hours)**: read docs/tutorial videos and implement a tiny piece; write progress note (1–3 lines) in README.

Exact checklist for each commit

* Code builds on Ubuntu with `cmake` + `make`.
* Provide sample input model download command in README.
* Add a small test (run script that captures 10 frames and outputs `test_results.txt`).
* Each week: `progress/Week-N.md` describing what worked, what failed, next steps.

Interviews — exact questions to prepare and how to answer
C++ (30–40%):

* Memory ownership: explain `unique_ptr` vs raw pointer and when to use each. Have a 3-line code example.
* STL choice: “why unordered\_map vs map” — explain O(1) vs O(log n).
* Be ready to read a short snippet and explain output. Practice 10 short snippets.

CV on edge (30–40%):

* Explain blob preprocessing steps and why input size matters. Cite `blobFromImage`. ([OpenCV Documentation][1])
* Explain model choice: MobileNet-SSD is small & fast on CPU; YOLO tiny variants are another option. Know pros/cons. ([GitHub][4])

DSA (10–20%):

* Sliding window problems, two pointers, hashmap counts. Show 1-2 examples from your code.

Linux (10%):

* Show you can compile, run, and run background scripts. Know basic commands: `ssh`, `scp`, `tail -f`, `systemctl` (optional).

Qt/QML (10%):

* Explain main thread vs worker thread, how you pass frames safely, and why you chose QQuickImageProvider or `QImage` approach. ([Medium][2])

Common failure modes and fixes (be proactive)

* App too slow: reduce input size, increase frame skip, switch to lighter model (MobileNet-SSD), use `setPreferableBackend`/`Target`. ([LearnOpenCV][3])
* Model mismatch (shape errors): ensure `blobFromImage` params and `net` input sizes match model; read OpenCV docs. ([OpenCV Documentation][1])
* UI freezes: you ran inference in the main thread. Move DNN to worker thread. Use `signals/slots`. ([Medium][2])
* Git hygiene: commit often, descriptive messages.

What to show Bhairav Robotics (exact)

* Email subject: `Detector-GUI — demo + resume — Dhanush Sai` with a short body: 2 lines + link to repo + offer to demo live. Attach PDF one-pager.
* In repo README top: “Short demo video (90s) — run `scripts/run.sh`” — make it trivial for them to test.
* In the call/demo: open `demo.mp4`, then run the app and show the code file where detection runs (they will ask). Be ready to explain tradeoffs.

Model choices — what to use now (fast wins)

* **Start with MobileNet-SSD (Caffe)** — easiest to load with OpenCV DNN and fast enough on CPU. ([GitHub][4])
* If you have time and want better accuracy, convert a YOLOv5/YOLOv8 or YOLOx model to ONNX and load via OpenCV DNN. Use LearnOpenCV guides. ([LearnOpenCV][7])

Small but critical extra tips

* Pin 1–3 repos on your GitHub profile (Project IRIS + Detector-GUI). Make sure Project IRIS README is tidy.
* Make your resume say “Can demo Detector-GUI on request — runs on Ubuntu.”
* Record your terminal outputs for setup commands so you can show exact steps if they ask.

Deliverables checklist (must have at the end of 8 weeks)

* Public GitHub `Detector-GUI` with:

  * `src/` (clean code), `CMakeLists.txt`, `scripts/run.sh`
  * `README.md` (how to download models, build, run, troubleshooting)
  * `demo.mp4` (90–120s)
  * `docs/onepager.pdf`
* Ability to demo live in 2 minutes.
* 10 solved DSA problems in `src/algorithms/` (C++).

Time allocation summary (8 weeks, 56 days)

* \~50% coding and integration (OpenCV, DNN, Qt)
* \~20% C++ & DSA practice
* \~10% Linux and deployment
* \~10% docs, demo video, README polish
* \~10% buffer / fixing blockers


[1]: https://docs.opencv.org/3.4/d6/d0f/group__dnn.html?utm_source=chatgpt.com "OpenCV: Deep Neural Network module"
[2]: https://medium.com/%40yunus.temurlenk1995/sending-opencv-images-to-qml-bridging-computer-vision-and-modern-ui-f8fafd7b873d?utm_source=chatgpt.com "Sending OpenCV Images to QML: Bridging Computer ..."
[3]: https://learnopencv.com/deep-learning-with-opencvs-dnn-module-a-definitive-guide/?utm_source=chatgpt.com "Deep Learning with OpenCV DNN Module: A Definitive ..."
[4]: https://github.com/chuanqi305/MobileNet-SSD?utm_source=chatgpt.com "chuanqi305/MobileNet-SSD"
[5]: https://docs.opencv.org/4.x/da/d9d/tutorial_dnn_yolo.html?utm_source=chatgpt.com "Running pre-trained YOLO model in OpenCV"
[6]: https://www.learncpp.com/?utm_source=chatgpt.com "Learn C++ – Skill up with our free tutorials"
[7]: https://learnopencv.com/object-detection-using-yolov5-and-opencv-dnn-in-c-and-python/?utm_source=chatgpt.com "Object Detection using YOLOv5 OpenCV DNN in C++ and ..."
