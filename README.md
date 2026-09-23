## How to Build and Run
<one or two shell commands to compile and launch the shell>

## What Works
<bullet list — tick off each functional requirement you implemented>

## What Doesn't Work / Known Issues
<honest statement; "none" is fine if everything works>

## AI Tools Used
<name each tool; e.g., "GitHub Copilot Chat (VS Code), ChatGPT-4o">

## Where to Find the AI Critique
<point to the specific file(s) and section(s) in ai_log/ where you:
 - identified an AI error and corrected it (cite the OS concept involved)
 - questioned a correct but questionable AI design choice>

## OS Concepts Demonstrated
<for each concept below, one sentence pointing to the relevant function/line in your code>
- fork()–exec()–wait() lifecycle
- File descriptor inheritance and dup2()
- Pipe as IPC (kernel buffer, write-end reference counting)
- Signal handling (SIGINT survival)
- Zombie prevention

## Test Evidence
<for each test case, the exact command and the shell output as a terminal transcript>
Minimum: multi-argument command, pipe, background process, one edge case.