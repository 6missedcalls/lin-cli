# Lin CLI — C++ Terminal Client for Linear

## Project
You are building `lin` — a fast, terminal-native CLI client for Linear (project management) written in C++. This is a portfolio project demonstrating systems-level C++ competency.

## Phase 1: Planning Only (DO NOT WRITE CODE YET)

### Your Task
Read the full Linear GraphQL API schema at `docs/graphql-docs-full.md` (288KB — all queries, mutations, 52 object types with 764 fields, 71 enums, 110 input types). Parse it thoroughly before designing anything.

Produce a comprehensive architecture document at `ARCHITECTURE.md` with ALL of the following:

### 1. API Coverage Map
Go through EVERY query and mutation in the schema. For each one, determine:
- Whether it belongs in the CLI (yes/no/later)
- Which module it maps to
- What CLI command would invoke it

Group into modules:
- **Issues** — CRUD, search, filtering, bulk operations, relations, attachments, subscribers
- **Projects** — CRUD, milestones, updates, members, status
- **Teams** — list, members, settings, workflow states, labels, cycles
- **Cycles** — CRUD, issues within cycle, active cycle
- **Users** — list, me, assignments
- **Labels** — CRUD, team labels vs workspace labels
- **Comments** — CRUD on issues, project updates
- **Documents** — CRUD, project docs
- **Favorites** — add/remove/list
- **Notifications** — list, mark read, archive
- **Webhooks** — CRUD
- **Custom Views** — list, create, apply filters
- **Roadmaps** — list, projects within roadmap
- **Initiatives** — list, projects within initiative
- **Search** — full text search across issues/projects/documents
- **Workflow States** — list per team, transitions
- **Integrations** — list active integrations
- **Organization** — settings, subscription info

### 2. Data Models
For each core object type (Issue, Project, Team, Cycle, User, Label, Comment, Document, Notification, CustomView, Roadmap, Initiative, Attachment, Favorite, WorkflowState, IssueRelation), define:
- The C++ struct with field types
- Which fields to include (pick what's useful for CLI display — not every field)
- JSON parsing approach
- Display format (table row, detail view, JSON output)

### 3. Module Architecture
Each module should be structured as:
```
src/modules/<name>/
  model.h        — data structs
  api.h / api.cpp — GraphQL queries/mutations, HTTP calls, response parsing
  commands.h / commands.cpp — CLI command handlers
```

### 4. Core Infrastructure
Design these shared components:
- **HTTP client** — libcurl wrapper for GraphQL POST requests to https://api.linear.app/graphql
- **JSON parsing** — nlohmann/json or rapidjson (pick one and justify)
- **Auth** — API key from env var (LINEAR_API_KEY) or config file (~/.config/lin/config.toml)
- **Output formatting** — table renderer (column alignment, truncation), detail view, raw JSON mode (`--json` flag), color support (ANSI), piping detection (no color when piped)
- **Pagination** — cursor-based relay-style (Linear uses `nodes`, `edges`, `pageInfo` with `hasNextPage`/`endCursor`)
- **Filtering** — translate CLI flags to Linear's filter input types (IssueFilter, ProjectFilter, etc.)
- **Error handling** — GraphQL errors, network errors, auth errors, rate limiting (with retry)
- **Config** — workspace selection, default team, output preferences, stored in TOML
- **Cache** — optional local SQLite cache for slow-changing data (teams, users, labels, workflow states)

### 5. CLI Command Tree
Design the FULL command tree. For EVERY command specify:
- Full syntax with all flags and arguments
- Which GraphQL query/mutation it calls (by name from the schema)
- Output format (table columns or detail fields)
- Example usage

```
lin issues [list|create|update|delete|show|search|assign|label|move|relate|attach|subscribe|bulk]
lin projects [list|create|update|delete|show|milestones|updates|members]
lin teams [list|show|members|states|labels|cycles]
lin cycles [list|show|current|create|update|issues|add|remove]
lin labels [list|create|update|delete]
lin comments [list|create|update|delete]
lin docs [list|create|update|delete|show]
lin views [list|create|show]
lin notifications [list|read|archive|snooze]
lin favorites [list|add|remove]
lin roadmaps [list|show]
lin initiatives [list|show]
lin search <query>
lin me — show current user info, assigned issues, notifications
lin config [set|get|list|init] — manage settings
lin tui — launch interactive TUI (Phase 2, FTXUI-based)
```

### 6. Build System
- CMake-based build
- Dependencies: libcurl, nlohmann/json, FTXUI (TUI — phase 2), SQLite3 (cache), toml++ (config), CLI11 (arg parsing)
- Target: macOS arm64 primary, Linux x86_64 secondary
- Single static binary output goal
- Compiler: clang++ with C++20
- Include a Makefile wrapper for convenience (`make build`, `make install`, `make test`)

### 7. Implementation Order
- Phase 1: Core infra (HTTP client, JSON, auth, config, output formatting, pagination) + Issues module (most complex, proves the full pattern)
- Phase 2: Teams, Labels, Workflow States, Users (supporting data needed by Issues)
- Phase 3: Projects, Cycles, Comments
- Phase 4: Everything else (docs, views, notifications, favorites, roadmaps, initiatives, search)
- Phase 5: TUI mode with FTXUI (interactive kanban board, issue detail, vim keybindings)
- Phase 6: Local SQLite cache, offline issue viewing

### 8. Testing Strategy
- Unit tests for JSON parsing, output formatting, filter construction
- Integration tests against Linear API (with real API key)
- Mock HTTP layer for offline testing

## Output
Write ARCHITECTURE.md with ALL of the above sections. Be exhaustive — map every query, every mutation, every command. This document is the single source of truth for all implementation work.

DO NOT write any C++ code. Planning only. The architecture doc should be thorough enough that a separate implementation agent can build from it without asking questions.
