<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-20-blue?style=flat-square&logo=cplusplus" alt="C++20">
  <img src="https://img.shields.io/badge/platform-macOS%20%7C%20Linux-lightgrey?style=flat-square" alt="Platform">
  <img src="https://img.shields.io/badge/license-MIT-green?style=flat-square" alt="License">
</p>

<pre align="center">
  ██╗     ██╗███╗   ██╗
  ██║     ██║████╗  ██║
  ██║     ██║██╔██╗ ██║
  ██║     ██║██║╚██╗██║
  ███████╗██║██║ ╚████║
  ╚══════╝╚═╝╚═╝  ╚═══╝
</pre>

<h3 align="center">Fast, terminal-native client for <a href="https://linear.app">Linear</a></h3>

<p align="center">
  Full <a href="https://linear.app">Linear</a> project management from your terminal.<br>
  18 modules &middot; 50+ commands &middot; interactive TUI &middot; built for humans and AI agents alike.
</p>

---

## Why lin?

[Linear](https://linear.app) is a project management tool used by engineering teams. **lin** brings the full Linear workflow to your terminal — no browser needed.

- **Fast** — native C++ binary, sub-100ms response times, zero runtime overhead
- **Complete** — issues, projects, cycles, teams, labels, comments, docs, notifications, search, and more
- **AI-friendly** — every command supports `--json` for structured output, purpose-built for LLM tool use
- **Interactive** — full TUI with kanban board, vim-style navigation, and inline editing
- **Portable** — single binary, no runtime dependencies

```
$ lin issues list
IDENTIFIER  PRIORITY  TITLE                                     STATE        ASSIGNEE
----------  --------  ----------------------------------------  -----------  ----------
ENG-423     Urgent    Fix auth token refresh on session expiry   In Progress  Alice
ENG-419     High      Add rate limiting to public API endpoints  In Progress  Bob
ENG-417     Normal    Update onboarding flow copy                Todo         Alice
ENG-415     Low       Clean up deprecated v1 API routes          Backlog      Unassigned
```

## Getting started

### 1. Install

**Homebrew** (macOS / Linux):

```sh
brew tap 6missedcalls/lin
brew install lin
```

**Shell script** (macOS / Linux):

```sh
curl -fsSL https://raw.githubusercontent.com/6missedcalls/lin-cli/main/install.sh | sh
```

**Prebuilt binaries**: download from [GitHub Releases](https://github.com/6missedcalls/lin-cli/releases) for macOS (arm64 / x86_64) and Linux (x86_64).

**Build from source**:

```sh
# install prerequisites
# macOS:  brew install cmake curl sqlite3
# Ubuntu: sudo apt install cmake libcurl4-openssl-dev libsqlite3-dev build-essential

git clone https://github.com/6missedcalls/lin-cli.git
cd lin-cli
make install    # builds + installs to /usr/local/bin
```

All library dependencies (CLI11, nlohmann/json, toml++, FTXUI) are fetched automatically by CMake.

### 2. Authenticate

Get your API key from [Linear Settings > API](https://linear.app/settings/api), then:

```sh
# Option A: environment variable (add to ~/.zshrc or ~/.bashrc to persist)
export LINEAR_API_KEY="lin_api_..."

# Option B: save to config file
lin config init
```

### 3. Verify

```sh
$ lin me
Name   Alice Chen
Email  alice@yourcompany.com
ID     xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
```

You're ready. Run `lin --help` to see all commands, or keep reading.

## Usage

```
lin <command> [subcommand] [flags]
```

Global flags (`--json`, `--csv`, `--no-color`, `--team`) work in any position:

```sh
lin issues list --json          # structured JSON output
lin --json issues list          # same thing
lin issues list --team "Eng"    # filter by team
```

### Command overview

| Group | Commands | Description |
|-------|----------|-------------|
| **Work Items** | `issues` `projects` `cycles` `search` | Create, list, update, and search your work |
| **Workspace** | `teams` `labels` `users` `views` `initiatives` | Manage workspace structure and metadata |
| **Collaborate** | `comments` `docs` `notifications` `favorites` `webhooks` | Communication and integrations |
| **Admin** | `org` `rate-limit` `integrations` `config` `cache` | Organization settings and CLI config |
| **Interactive** | `tui` `me` | Kanban board and user profile |

Run any command bare to see its subcommands:

```sh
lin issues          # shows all issue subcommands
lin projects        # shows all project subcommands
```

### Common workflows

```sh
# Browse issues
lin issues list
lin issues list --team "Engineering" --state "In Progress"
lin issues show ENG-123

# Create and manage
lin issues create --title "Fix auth timeout" --team "Engineering" --priority 2
lin issues update ENG-123 --state "Done"
lin issues assign ENG-123 --user "alice@company.com"

# Search across everything
lin search "payment processing"

# Quick glance
lin me                           # your profile
lin notifications list           # unread notifications
lin cycles current --team "Eng"  # active sprint
```

### JSON output for AI agents

Every command supports `--json`, producing structured output for LLM tool use and scripting:

```sh
$ lin me --json
{
  "id": "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx",
  "name": "Alice Chen",
  "email": "alice@yourcompany.com",
  "displayName": "Alice"
}
```

Mutation commands emit `{"success": true, "message": "..."}` or `{"success": false, "error": "..."}` when `--json` is active.

### TUI mode

```sh
lin tui
lin tui --team "Engineering"
```

Interactive kanban board with vim-style keybindings:

| Key | Action |
|-----|--------|
| `j` / `k` | Navigate up / down |
| `h` / `l` | Switch columns |
| `Enter` | Open issue detail |
| `p` | Set priority |
| `s` | Set state |
| `a` | Assign |
| `/` | Search |
| `q` / `Esc` | Back / quit |

Changes made in the detail view (priority, state, assignee) are reflected on the kanban board when you return.

## Configuration

```sh
lin config init                        # interactive setup
lin config set defaults.team "Eng"     # default team filter
lin config set defaults.output json    # default output format
lin config set display.page_size 100   # results per page
lin config list                        # show all settings
```

Stored at `~/.config/lin/config.toml`:

| Key | Values | Default |
|-----|--------|---------|
| `api_key` | `lin_api_...` | — |
| `defaults.team` | team name or key | — |
| `defaults.output` | `table` `json` `csv` | `table` |
| `display.color` | `true` `false` | `true` |
| `display.page_size` | `1` – `250` | `50` |
| `display.date_format` | `relative` `iso` `short` | `relative` |

## Architecture

```
src/
├── main.cpp                  Entry point, CLI registration
├── core/
│   ├── http_client.{h,cpp}   libcurl wrapper, TLS, rate-limit headers
│   ├── graphql.{h,cpp}       GraphQL query execution, variable binding
│   ├── auth.{h,cpp}          API key resolution (env var / config file)
│   ├── config.{h,cpp}        TOML config read/write
│   ├── output.{h,cpp}        Table renderer, detail renderer, CSV, JSON
│   ├── color.{h,cpp}         ANSI color, pipe detection, hex-to-RGB
│   ├── error.{h,cpp}         Typed errors, retry-after, rate limiting
│   ├── filter.{h,cpp}        CLI flags → GraphQL filter objects
│   ├── paginator.{h,cpp}     Cursor-based relay pagination
│   ├── cache.{h,cpp}         SQLite cache for slow-changing data
│   └── types.h               Connection<T>, PageInfo
├── modules/
│   └── <name>/               One directory per domain
│       ├── model.h            Data structs + JSON deserialization
│       ├── api.{h,cpp}        GraphQL queries/mutations
│       └── commands.{h,cpp}   CLI11 command registration + handlers
└── tui/
    ├── app.{h,cpp}            TUI controller, view routing
    ├── kanban.{h,cpp}         Kanban board columns + cards
    ├── issue_detail.{h,cpp}   Issue detail view, inline pickers
    ├── picker.{h,cpp}         Overlay picker (priority, state, assignee)
    ├── search.{h,cpp}         Search overlay
    └── theme.{h,cpp}          TUI color palette
```

Each module follows a consistent three-file pattern: **model** (data) → **api** (network) → **commands** (UI). Core infrastructure is shared across all modules.

## Development

```sh
make build       # release build (optimized)
make debug       # debug build (symbols, sanitizers)
make test        # build + run 210 tests via CTest
make clean       # remove build artifacts
make format      # clang-format all source files
make lint        # clang-tidy static analysis
```

### Tech stack

| Layer | Technology |
|-------|-----------|
| Language | C++20 (clang++) |
| Build | CMake 3.20+ |
| HTTP | [libcurl](https://curl.se/libcurl/) |
| JSON | [nlohmann/json](https://github.com/nlohmann/json) v3.11.3 |
| CLI | [CLI11](https://github.com/CLIUtils/CLI11) v2.4.2 |
| Config | [toml++](https://github.com/marzer/tomlplusplus) v3.4.0 |
| TUI | [FTXUI](https://github.com/ArthurSonzogni/ftxui) v5.0.0 |
| Cache | [SQLite3](https://www.sqlite.org/) |
| Tests | [GoogleTest](https://github.com/google/googletest) v1.15.2 |

### Running tests

```sh
make test
# or directly:
cd build && ctest --output-on-failure
```

The test suite covers JSON parsing, output formatting, filter construction, pagination, error handling, caching, and TUI state management. All tests run offline — no API key required.

## License

[MIT](LICENSE)

---

<p align="center">
  Built by <a href="https://github.com/6missedcalls">6missedcalls</a>
</p>
