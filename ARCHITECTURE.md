# Lin CLI — Architecture Document

> Single source of truth for all implementation work.
> Generated from the Linear GraphQL API schema (`docs/graphql-docs-full.md`).

---

## Table of Contents

1. [API Coverage Map](#1-api-coverage-map)
2. [Data Models](#2-data-models)
3. [Module Architecture](#3-module-architecture)
4. [Core Infrastructure](#4-core-infrastructure)
5. [CLI Command Tree](#5-cli-command-tree)
6. [Build System](#6-build-system)
7. [Implementation Order](#7-implementation-order)
8. [Testing Strategy](#8-testing-strategy)

---

## 1. API Coverage Map

Every query and mutation in the Linear GraphQL schema, categorized by module, CLI inclusion, and command mapping.

Legend:
- **Yes** — Include in CLI
- **No** — Skip (internal, irrelevant, or OAuth/SSO flow)
- **Later** — Include in a future phase

---

### 1.1 Issues Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `issues(filter, before, after, first, last, includeArchived, orderBy, sort)` | Yes | `lin issues list` | Primary issue listing with filtering |
| `issue(id)` | Yes | `lin issues show <id>` | Single issue detail |
| `searchIssues(filter, term, includeComments, teamId)` | Yes | `lin issues search` | Full-text search |
| `issueSearch(filter, query)` | No | — | Deprecated, use `searchIssues` |
| `issueVcsBranchSearch(branchName)` | Yes | `lin issues branch <name>` | Find issue by git branch |
| `issueFigmaFileKeySearch(fileKey)` | No | — | Figma-specific |
| `issuePriorityValues()` | Yes | (internal) | Used to display priority labels |
| `issueFilterSuggestion(prompt)` | No | — | AI-powered, not CLI-relevant |
| `issueRepositorySuggestions(...)` | No | — | Internal agent feature |
| `issueRelations(...)` | Yes | `lin issues relations` | All issue relations |
| `issueRelation(id)` | Yes | (internal) | Single relation lookup |
| `issueLabels(filter, ...)` | Yes | `lin labels list` | → Labels module |
| `issueLabel(id)` | Yes | `lin labels show <id>` | → Labels module |
| `issueImportCheckCSV(...)` | No | — | Import tooling |
| `issueImportCheckSync(...)` | No | — | Import tooling |
| `issueImportJqlCheck(...)` | No | — | Import tooling |
| `issueToReleases(...)` | No | — | Alpha release feature |
| `issueToRelease(id)` | No | — | Alpha release feature |

#### Mutations

| Mutation | Include | Command | Notes |
|----------|---------|---------|-------|
| `issueCreate(input)` | Yes | `lin issues create` | Create new issue |
| `issueBatchCreate(input)` | Later | `lin issues bulk create` | Batch create |
| `issueUpdate(input, id)` | Yes | `lin issues update <id>` | Update issue fields |
| `issueBatchUpdate(input, ids)` | Yes | `lin issues bulk update` | Bulk update |
| `issueArchive(trash, id)` | Yes | `lin issues archive <id>` | Archive/trash issue |
| `issueUnarchive(id)` | Yes | `lin issues unarchive <id>` | Restore archived |
| `issueDelete(permanentlyDelete, id)` | Yes | `lin issues delete <id>` | Delete/trash issue |
| `issueAddLabel(labelId, id)` | Yes | `lin issues label add <id> <label>` | Add label |
| `issueRemoveLabel(labelId, id)` | Yes | `lin issues label remove <id> <label>` | Remove label |
| `issueSubscribe(userId, id)` | Yes | `lin issues subscribe <id>` | Subscribe to issue |
| `issueUnsubscribe(userId, id)` | Yes | `lin issues unsubscribe <id>` | Unsubscribe |
| `issueReminder(reminderAt, id)` | Later | — | Reminder feature |
| `issueRelationCreate(input)` | Yes | `lin issues relate <id> <related_id>` | Create relation |
| `issueRelationUpdate(input, id)` | Yes | (internal) | Update relation type |
| `issueRelationDelete(id)` | Yes | `lin issues unrelate <id>` | Delete relation |
| `issueDescriptionUpdateFromFront(...)` | No | — | Internal Front integration |
| `issueExternalSyncDisable(...)` | No | — | External sync management |
| `issueImportCreate*(...)` | No | — | Import jobs (GitHub, Jira, Asana, etc.) |
| `issueImportDelete(...)` | No | — | Import management |
| `issueImportProcess(...)` | No | — | Import management |
| `issueImportUpdate(...)` | No | — | Import management |
| `issueToReleaseCreate(...)` | No | — | Alpha release feature |
| `issueToReleaseDelete*(...)` | No | — | Alpha release feature |

---

### 1.2 Projects Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `projects(filter, ...)` | Yes | `lin projects list` | List all projects |
| `project(id)` | Yes | `lin projects show <id>` | Single project detail |
| `searchProjects(term, ...)` | Yes | `lin projects search` | Full-text search |
| `projectFilterSuggestion(prompt)` | No | — | AI filter suggestion |
| `projectUpdates(filter, ...)` | Yes | `lin projects updates <id>` | Project updates |
| `projectUpdate(id)` | Yes | (internal) | Single update detail |
| `projectStatuses(...)` | Yes | (internal) | List available statuses |
| `projectStatus(id)` | Yes | (internal) | Single status |
| `projectStatusProjectCount(id)` | No | — | Internal |
| `projectRelations(...)` | Later | `lin projects relations` | Project relations |
| `projectRelation(id)` | Later | (internal) | Single relation |
| `projectMilestones(filter, ...)` | Yes | `lin projects milestones <id>` | List milestones |
| `projectMilestone(id)` | Yes | (internal) | Single milestone |
| `projectLabels(filter, ...)` | Later | `lin projects labels` | Project-level labels |
| `projectLabel(id)` | Later | (internal) | Single project label |

#### Mutations

| Mutation | Include | Command | Notes |
|----------|---------|---------|-------|
| `projectCreate(input)` | Yes | `lin projects create` | Create project |
| `projectUpdate(input, id)` | Yes | `lin projects update <id>` | Update project |
| `projectDelete(id)` | Yes | `lin projects delete <id>` | Delete/trash project |
| `projectUnarchive(id)` | Later | `lin projects unarchive <id>` | Restore |
| `projectAddLabel(labelId, id)` | Later | `lin projects label add` | Add label |
| `projectRemoveLabel(labelId, id)` | Later | `lin projects label remove` | Remove label |
| `projectExternalSyncDisable(...)` | No | — | External sync |
| `projectReassignStatus(...)` | No | — | Internal |
| `projectUpdateCreate(input)` | Yes | `lin projects updates create <id>` | Post update |
| `projectUpdateUpdate(input, id)` | Later | `lin projects updates edit <id>` | Edit update |
| `projectUpdateArchive(id)` | Later | — | Archive update |
| `projectUpdateUnarchive(id)` | Later | — | Restore update |
| `createProjectUpdateReminder(...)` | No | — | Notification feature |
| `projectStatusCreate(input)` | No | — | Admin feature |
| `projectStatusUpdate(input, id)` | No | — | Admin feature |
| `projectStatusArchive(id)` | No | — | Admin feature |
| `projectStatusUnarchive(id)` | No | — | Admin feature |
| `projectRelationCreate(input)` | Later | `lin projects relate` | Create relation |
| `projectRelationUpdate(input, id)` | Later | — | Update relation |
| `projectRelationDelete(id)` | Later | `lin projects unrelate` | Delete relation |
| `projectMilestoneCreate(input)` | Yes | `lin projects milestones create` | Create milestone |
| `projectMilestoneUpdate(input, id)` | Yes | `lin projects milestones update <id>` | Update milestone |
| `projectMilestoneDelete(id)` | Yes | `lin projects milestones delete <id>` | Delete milestone |
| `projectMilestoneMove(...)` | No | — | Internal |
| `projectLabelCreate(input)` | Later | — | Project label management |
| `projectLabelUpdate(input, id)` | Later | — | Project label management |
| `projectLabelDelete(id)` | Later | — | Project label management |
| `projectLabelRetire(id)` | No | — | Rarely needed |
| `projectLabelRestore(id)` | No | — | Rarely needed |

---

### 1.3 Teams Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `teams(filter, ...)` | Yes | `lin teams list` | List all teams |
| `team(id)` | Yes | `lin teams show <id>` | Team detail |
| `administrableTeams(filter, ...)` | No | — | Admin feature |
| `teamMemberships(...)` | Yes | `lin teams members <id>` | Team memberships |
| `teamMembership(id)` | Yes | (internal) | Single membership |

#### Mutations

| Mutation | Include | Command | Notes |
|----------|---------|---------|-------|
| `teamCreate(input)` | No | — | Admin-only, rare from CLI |
| `teamUpdate(input, id)` | No | — | Admin-only |
| `teamDelete(id)` | No | — | Admin-only, destructive |
| `teamUnarchive(id)` | No | — | Admin-only |
| `teamCyclesDelete(id)` | No | — | Admin-only, destructive |
| `teamMembershipCreate(input)` | No | — | Admin-only |
| `teamMembershipUpdate(input, id)` | No | — | Admin-only |
| `teamMembershipDelete(id)` | No | — | Admin-only |
| `teamKeyDelete(id)` | No | — | Admin-only |

---

### 1.4 Cycles Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `cycles(filter, ...)` | Yes | `lin cycles list` | List cycles |
| `cycle(id)` | Yes | `lin cycles show <id>` | Cycle detail |

#### Mutations

| Mutation | Include | Command | Notes |
|----------|---------|---------|-------|
| `cycleCreate(input)` | Yes | `lin cycles create` | Create cycle |
| `cycleUpdate(input, id)` | Yes | `lin cycles update <id>` | Update cycle |
| `cycleArchive(id)` | Yes | `lin cycles archive <id>` | Archive cycle |
| `cycleShiftAll(input)` | No | — | Complex scheduling, admin |
| `cycleStartUpcomingCycleToday(id)` | No | — | Admin scheduling |

---

### 1.5 Users Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `viewer()` | Yes | `lin me` | Current authenticated user |
| `users(filter, ...)` | Yes | `lin users list` | List organization users |
| `user(id)` | Yes | `lin users show <id>` | User detail |
| `userSettings()` | Later | `lin config show` | User settings |
| `userSessions(id)` | No | — | Admin-only |

#### Mutations

| Mutation | Include | Command | Notes |
|----------|---------|---------|-------|
| `userUpdate(input, id)` | No | — | Profile editing, use web UI |
| `userSettingsUpdate(input, id)` | No | — | Settings, use web UI |
| `userSettingsFlagsReset(flags)` | No | — | Internal |
| `userFlagUpdate(...)` | No | — | Internal |
| `userDiscordConnect(...)` | No | — | OAuth flow |
| `userExternalUserDisconnect(...)` | No | — | OAuth flow |
| `userChangeRole(...)` | No | — | Admin-only |
| `userSuspend(id)` | No | — | Admin-only |
| `userUnsuspend(id)` | No | — | Admin-only |
| `userRevokeAllSessions(id)` | No | — | Admin-only |
| `userRevokeSession(...)` | No | — | Admin-only |
| `userUnlinkFromIdentityProvider(id)` | No | — | Admin-only |
| `notificationCategoryChannelSubscriptionUpdate(...)` | No | — | Notification prefs |

---

### 1.6 Labels Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `issueLabels(filter, ...)` | Yes | `lin labels list` | List all labels |
| `issueLabel(id)` | Yes | `lin labels show <id>` | Label detail |

#### Mutations

| Mutation | Include | Command | Notes |
|----------|---------|---------|-------|
| `issueLabelCreate(input)` | Yes | `lin labels create` | Create label |
| `issueLabelUpdate(input, id)` | Yes | `lin labels update <id>` | Update label |
| `issueLabelDelete(id)` | Yes | `lin labels delete <id>` | Delete label |
| `issueLabelRetire(id)` | No | — | Rarely used |
| `issueLabelRestore(id)` | No | — | Rarely used |

---

### 1.7 Comments Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `comments(filter, ...)` | Yes | `lin comments list` | List comments (filtered by issue) |
| `comment(id)` | Yes | `lin comments show <id>` | Single comment |

#### Mutations

| Mutation | Include | Command | Notes |
|----------|---------|---------|-------|
| `commentCreate(input)` | Yes | `lin comments create` | Create comment on issue |
| `commentUpdate(input, id)` | Yes | `lin comments update <id>` | Edit comment |
| `commentDelete(id)` | Yes | `lin comments delete <id>` | Delete comment |
| `commentResolve(id)` | Later | `lin comments resolve <id>` | Resolve thread |
| `commentUnresolve(id)` | Later | `lin comments unresolve <id>` | Unresolve thread |

---

### 1.8 Documents Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `documents(filter, ...)` | Yes | `lin docs list` | List documents |
| `document(id)` | Yes | `lin docs show <id>` | Document detail |
| `searchDocuments(term, ...)` | Yes | `lin docs search` | Full-text search |
| `documentContentHistory(id)` | No | — | Content versioning, complex |

#### Mutations

| Mutation | Include | Command | Notes |
|----------|---------|---------|-------|
| `documentCreate(input)` | Yes | `lin docs create` | Create document |
| `documentUpdate(input, id)` | Yes | `lin docs update <id>` | Update document |
| `documentDelete(id)` | Yes | `lin docs delete <id>` | Delete document |
| `documentUnarchive(id)` | Later | `lin docs unarchive <id>` | Restore document |

---

### 1.9 Favorites Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `favorites(...)` | Yes | `lin favorites list` | List favorites |
| `favorite(id)` | Yes | (internal) | Single favorite |

#### Mutations

| Mutation | Include | Command | Notes |
|----------|---------|---------|-------|
| `favoriteCreate(input)` | Yes | `lin favorites add` | Add favorite |
| `favoriteUpdate(input, id)` | Later | — | Reorder favorites |
| `favoriteDelete(id)` | Yes | `lin favorites remove <id>` | Remove favorite |

---

### 1.10 Notifications Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `notifications(filter, ...)` | Yes | `lin notifications list` | List notifications |
| `notification(id)` | Yes | `lin notifications show <id>` | Single notification |
| `notificationsUnreadCount()` | Yes | `lin notifications count` | Unread count (internal) |
| `notificationSubscriptions(...)` | Later | — | Subscription management |
| `notificationSubscription(id)` | Later | — | Single subscription |

#### Mutations

| Mutation | Include | Command | Notes |
|----------|---------|---------|-------|
| `notificationUpdate(input, id)` | Yes | `lin notifications read <id>` | Mark read |
| `notificationMarkReadAll(...)` | Yes | `lin notifications read --all` | Mark all read |
| `notificationMarkUnreadAll(...)` | Later | — | Mark unread |
| `notificationSnoozeAll(...)` | Yes | `lin notifications snooze <id>` | Snooze |
| `notificationUnsnoozeAll(...)` | Later | — | Unsnooze |
| `notificationArchive(id)` | Yes | `lin notifications archive <id>` | Archive |
| `notificationArchiveAll(...)` | Later | `lin notifications archive --all` | Archive all |
| `notificationUnarchive(id)` | Later | — | Unarchive |
| `notificationSubscriptionCreate(input)` | No | — | Complex subscription |
| `notificationSubscriptionUpdate(...)` | No | — | Complex subscription |

---

### 1.11 Webhooks Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `webhooks(...)` | Yes | `lin webhooks list` | List webhooks |
| `webhook(id)` | Yes | `lin webhooks show <id>` | Webhook detail |
| `failuresForOauthWebhooks(...)` | No | — | Internal |

#### Mutations

| Mutation | Include | Command | Notes |
|----------|---------|---------|-------|
| `webhookCreate(input)` | Yes | `lin webhooks create` | Create webhook |
| `webhookUpdate(input, id)` | Yes | `lin webhooks update <id>` | Update webhook |
| `webhookDelete(id)` | Yes | `lin webhooks delete <id>` | Delete webhook |
| `webhookRotateSecret(id)` | Later | `lin webhooks rotate <id>` | Rotate secret |

---

### 1.12 Custom Views Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `customViews(filter, ...)` | Yes | `lin views list` | List custom views |
| `customView(id)` | Yes | `lin views show <id>` | View detail |
| `customViewDetailsSuggestion(...)` | No | — | Internal |
| `customViewHasSubscribers(id)` | No | — | Internal |

#### Mutations

| Mutation | Include | Command | Notes |
|----------|---------|---------|-------|
| `customViewCreate(input)` | Yes | `lin views create` | Create view |
| `customViewUpdate(input, id)` | Later | `lin views update <id>` | Update view |
| `customViewDelete(id)` | Yes | `lin views delete <id>` | Delete view |

---

### 1.13 Roadmaps Module

> Note: Roadmaps are **deprecated** in Linear's schema. Initiatives replace them.

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `roadmaps(...)` | No | — | Deprecated — no `roadmaps` top-level query exists; access via Organization.roadmaps |

#### Mutations

| Mutation | Include | Command | Notes |
|----------|---------|---------|-------|
| `roadmapToProjectCreate(input)` | No | — | Deprecated |
| `roadmapToProjectUpdate(input, id)` | No | — | Deprecated |
| `roadmapToProjectDelete(id)` | No | — | Deprecated |

> Roadmaps are deprecated. The CLI will use Initiatives instead, which is the replacement feature.

---

### 1.14 Initiatives Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `initiatives(filter, ...)` | Yes | `lin initiatives list` | List initiatives |
| `initiative(id)` | Yes | `lin initiatives show <id>` | Initiative detail |
| `initiativeUpdates(filter, ...)` | Later | `lin initiatives updates <id>` | Initiative updates |
| `initiativeUpdate(id)` | Later | (internal) | Single update |
| `initiativeToProjects(...)` | Yes | (internal) | Initiative-project links |
| `initiativeToProject(id)` | Yes | (internal) | Single link |
| `initiativeRelations(...)` | Later | — | Initiative relations |
| `initiativeRelation(id)` | Later | — | Single relation |

#### Mutations

| Mutation | Include | Command | Notes |
|----------|---------|---------|-------|
| `initiativeCreate(input)` | Later | `lin initiatives create` | Create initiative |
| `initiativeUpdate(input, id)` | Later | `lin initiatives update <id>` | Update initiative |
| `initiativeArchive(id)` | Later | — | Archive |
| `initiativeUnarchive(id)` | Later | — | Unarchive |
| `initiativeDelete(id)` | Later | `lin initiatives delete <id>` | Delete |
| `initiativeToProjectCreate(input)` | Later | `lin initiatives add-project` | Link project |
| `initiativeToProjectUpdate(input, id)` | Later | — | Update link |
| `initiativeToProjectDelete(id)` | Later | `lin initiatives remove-project` | Remove link |
| `initiativeUpdateCreate(input)` | Later | `lin initiatives updates create` | Post update |
| `initiativeUpdateUpdate(input, id)` | Later | — | Edit update |
| `initiativeUpdateArchive(id)` | Later | — | Archive update |
| `initiativeUpdateUnarchive(id)` | Later | — | Unarchive update |
| `createInitiativeUpdateReminder(...)` | No | — | Notification feature |
| `initiativeRelationCreate(input)` | Later | — | Create relation |
| `initiativeRelationUpdate(input, id)` | Later | — | Update relation |
| `initiativeRelationDelete(id)` | Later | — | Delete relation |

---

### 1.15 Search Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `searchIssues(filter, term, ...)` | Yes | `lin search --type issues <query>` | Search issues |
| `searchProjects(term, ...)` | Yes | `lin search --type projects <query>` | Search projects |
| `searchDocuments(term, ...)` | Yes | `lin search --type docs <query>` | Search documents |
| `semanticSearch(query, types, ...)` | Yes | `lin search <query>` | Natural language search across types |

---

### 1.16 Workflow States Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `workflowStates(filter, ...)` | Yes | `lin teams states <team_id>` | List workflow states |
| `workflowState(id)` | Yes | (internal) | Single state |

#### Mutations

| Mutation | Include | Command | Notes |
|----------|---------|---------|-------|
| `workflowStateCreate(input)` | No | — | Admin feature |
| `workflowStateUpdate(input, id)` | No | — | Admin feature |
| `workflowStateArchive(id)` | No | — | Admin feature |

---

### 1.17 Integrations Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `integrations(...)` | Yes | `lin integrations list` | List active integrations |
| `integration(id)` | Yes | `lin integrations show <id>` | Integration detail |
| `integrationTemplates(...)` | No | — | Internal |
| `integrationTemplate(id)` | No | — | Internal |
| `integrationsSettings(id)` | No | — | Internal |
| `integrationHasScopes(...)` | No | — | Internal |
| `verifyGitHubEnterpriseServerInstallation(...)` | No | — | Internal |

#### Mutations

All integration mutations are OAuth/connection flows — **none included in CLI**. Integrations are set up via the Linear web UI.

---

### 1.18 Organization Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `organization()` | Yes | `lin org` | Organization info |
| `organizationExists(urlKey)` | No | — | Account setup |
| `organizationMeta(urlKey)` | No | — | Internal |
| `organizationInvites(...)` | No | — | Admin |
| `organizationInvite(id)` | No | — | Admin |
| `organizationInviteDetails(id)` | No | — | Admin |
| `organizationDomainClaimRequest(id)` | No | — | Internal |
| `archivedTeams()` | No | — | Internal |
| `rateLimitStatus()` | Yes | `lin rate-limit` | Check API rate limit |

#### Mutations

All organization mutations are admin operations — **none included in CLI** (use web UI).

---

### 1.19 Attachments Module

#### Queries

| Query | Include | Command | Notes |
|-------|---------|---------|-------|
| `attachments(filter, ...)` | Yes | `lin issues attachments <issue_id>` | List issue attachments |
| `attachment(id)` | Yes | (internal) | Single attachment |
| `attachmentsForURL(url)` | Later | — | URL-based lookup |
| `attachmentSources(...)` | No | — | Internal |

#### Mutations

| Mutation | Include | Command | Notes |
|----------|---------|---------|-------|
| `attachmentCreate(input)` | Yes | `lin issues attach <id>` | Create attachment |
| `attachmentUpdate(input, id)` | Later | — | Update attachment |
| `attachmentLinkURL(url, issueId)` | Yes | `lin issues attach <id> --url <url>` | Link URL to issue |
| `attachmentDelete(id)` | Yes | `lin issues detach <attachment_id>` | Delete attachment |
| `attachmentLinkGitHub*(...)` | No | — | GitHub-specific, auto via integration |
| `attachmentLinkGitLabMR(...)` | No | — | GitLab-specific |
| `attachmentLinkZendesk(...)` | No | — | Zendesk-specific |
| `attachmentLinkDiscord(...)` | No | — | Discord-specific |
| `attachmentLinkSlack(...)` | No | — | Slack-specific |
| `attachmentLinkFront(...)` | No | — | Front-specific |
| `attachmentLinkIntercom(...)` | No | — | Intercom-specific |
| `attachmentLinkJiraIssue(...)` | No | — | Jira-specific |
| `attachmentLinkSalesforce(...)` | No | — | Salesforce-specific |
| `attachmentSyncToSlack(...)` | No | — | Slack-specific |

---

### 1.20 Skipped APIs (Not Included)

These queries/mutations are explicitly excluded:

| Category | Reason |
|----------|--------|
| `agentSession*`, `agentActivity*` | Linear Agent (AI) internals |
| `customer*`, `customerTier*`, `customerStatus*`, `customerNeed*` | CRM feature, rarely used from CLI |
| `release*`, `releaseStage*`, `releasePipeline*` | Alpha feature |
| `template*` | Template management (web UI better suited) |
| `timeSchedule*` | Schedule management |
| `triageResponsibility*` | Triage config |
| `gitAutomation*` | Git automation config |
| `emoji*` | Custom emoji management |
| `emailIntakeAddress*` | Email config |
| `entityExternalLink*` | External links |
| `externalUsers(...)` | External user management |
| `viewPreferences*` | View configuration |
| `reaction*` | Emoji reactions |
| `pushSubscription*` | Push notifications |
| `auditEntries(...)` | Audit logs (admin) |
| Auth mutations (`emailUserAccountAuthChallenge`, `googleUserAccountAuth`, etc.) | OAuth/auth flows |
| File upload mutations (`fileUpload`, `importFileUpload`, etc.) | File upload (complex multipart) |
| `createCsvExportReport(...)` | Export feature |
| `contactCreate(...)` | Support contact |

---

## 2. Data Models

C++ structs for each core object type. Fields are selected for CLI display relevance.

All structs use `std::optional<T>` for nullable fields and `std::string` for IDs/dates (ISO 8601 strings).

### 2.1 Common Types

```cpp
// src/core/types.h

#include <optional>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct PageInfo {
    bool has_next_page = false;
    bool has_previous_page = false;
    std::optional<std::string> start_cursor;
    std::optional<std::string> end_cursor;
};

template<typename T>
struct Connection {
    std::vector<T> nodes;
    PageInfo page_info;
};

// JSON parsing via nlohmann/json ADL
void from_json(const json& j, PageInfo& p);

template<typename T>
void from_json(const json& j, Connection<T>& c);
```

### 2.2 Issue

```cpp
// src/modules/issues/model.h

struct Issue {
    std::string id;
    std::string created_at;
    std::string updated_at;
    std::optional<std::string> archived_at;

    double number;
    std::string title;
    double priority;                          // 0=None, 1=Urgent, 2=High, 3=Normal, 4=Low
    std::string priority_label;
    std::optional<double> estimate;
    std::string identifier;                   // e.g. "ENG-123"
    std::string url;
    std::string branch_name;

    std::optional<std::string> description;
    std::optional<std::string> due_date;
    std::optional<std::string> started_at;
    std::optional<std::string> completed_at;
    std::optional<std::string> canceled_at;
    bool trashed = false;

    // Nested references (IDs for list view, expanded for detail view)
    std::optional<std::string> team_id;
    std::optional<std::string> team_name;
    std::optional<std::string> team_key;

    std::optional<std::string> assignee_id;
    std::optional<std::string> assignee_name;

    std::optional<std::string> creator_id;
    std::optional<std::string> creator_name;

    std::optional<std::string> state_id;
    std::optional<std::string> state_name;
    std::optional<std::string> state_type;    // triage, backlog, unstarted, started, completed, canceled

    std::optional<std::string> project_id;
    std::optional<std::string> project_name;

    std::optional<std::string> cycle_id;
    std::optional<double> cycle_number;

    std::optional<std::string> parent_id;
    std::optional<std::string> parent_identifier;

    std::vector<std::string> label_ids;
    std::vector<std::string> label_names;
    std::vector<std::string> previous_identifiers;
};

// JSON: parse from GraphQL response "data.issue" or "data.issues.nodes[]"
void from_json(const json& j, Issue& i);
```

**Table display columns:** `identifier`, `priority_label`, `title`, `state_name`, `assignee_name`, `due_date`

**Detail view fields:** All fields above, plus `description`, `labels`, `url`, `branch_name`, `created_at`

### 2.3 Project

```cpp
// src/modules/projects/model.h

struct Project {
    std::string id;
    std::string created_at;
    std::string updated_at;

    std::string name;
    std::optional<std::string> description;
    std::optional<std::string> icon;
    std::optional<std::string> color;
    std::string slug_id;
    std::string url;
    int priority;                             // 0=None, 1=Urgent, 2=High, 3=Normal, 4=Low
    std::optional<std::string> priority_label;

    // Status
    std::optional<std::string> status_id;
    std::optional<std::string> status_name;
    std::optional<std::string> status_type;   // backlog, planned, started, paused, completed, canceled

    // Health
    std::optional<std::string> health;        // onTrack, atRisk, offTrack
    std::optional<std::string> health_updated_at;

    // Lead
    std::optional<std::string> lead_id;
    std::optional<std::string> lead_name;

    // Creator
    std::optional<std::string> creator_id;
    std::optional<std::string> creator_name;

    // Dates
    std::optional<std::string> start_date;
    std::optional<std::string> target_date;
    std::optional<std::string> started_at;
    std::optional<std::string> completed_at;
    std::optional<std::string> canceled_at;

    // Progress
    double progress = 0.0;
    double scope = 0.0;

    bool trashed = false;
};

void from_json(const json& j, Project& p);
```

**Table columns:** `name`, `status_name`, `health`, `lead_name`, `progress`, `target_date`

### 2.4 Team

```cpp
// src/modules/teams/model.h

struct Team {
    std::string id;
    std::string created_at;
    std::string updated_at;

    std::string name;
    std::string key;
    std::optional<std::string> description;
    std::optional<std::string> icon;
    std::optional<std::string> color;
    std::optional<std::string> timezone;
    std::string display_name;

    bool cycles_enabled = false;
    bool triage_enabled = false;
    bool private_team = false;
    int issue_count = 0;

    // Cycle settings
    double cycle_duration = 0;
    double cycle_cooldown_time = 0;
    double cycle_start_day = 0;

    // Estimation
    std::string issue_estimation_type;       // notUsed, exponential, fibonacci, linear, tShirt
};

void from_json(const json& j, Team& t);
```

**Table columns:** `key`, `name`, `issue_count`, `cycles_enabled`, `triage_enabled`

### 2.5 Cycle

```cpp
// src/modules/cycles/model.h

struct Cycle {
    std::string id;
    std::string created_at;
    std::string updated_at;

    double number;
    std::optional<std::string> name;
    std::optional<std::string> description;
    std::string starts_at;
    std::string ends_at;
    std::optional<std::string> completed_at;

    // Team
    std::optional<std::string> team_id;
    std::optional<std::string> team_name;

    // Status
    bool is_active = false;
    bool is_future = false;
    bool is_past = false;
    bool is_next = false;
    bool is_previous = false;

    double progress = 0.0;
};

void from_json(const json& j, Cycle& c);
```

**Table columns:** `number`, `name`, `starts_at`, `ends_at`, `progress`, `is_active`

### 2.6 User

```cpp
// src/modules/users/model.h

struct User {
    std::string id;
    std::string created_at;

    std::string name;
    std::string display_name;
    std::string email;
    std::optional<std::string> avatar_url;
    std::optional<std::string> description;
    std::optional<std::string> timezone;
    std::optional<std::string> last_seen;

    std::optional<std::string> status_emoji;
    std::optional<std::string> status_label;

    bool active = true;
    bool admin = false;
    bool guest = false;
    bool is_me = false;
};

void from_json(const json& j, User& u);
```

**Table columns:** `display_name`, `email`, `active`, `admin`

### 2.7 IssueLabel

```cpp
// src/modules/labels/model.h

struct IssueLabel {
    std::string id;
    std::string created_at;

    std::string name;
    std::optional<std::string> description;
    std::string color;
    bool is_group = false;

    // Parent (for grouped labels)
    std::optional<std::string> parent_id;
    std::optional<std::string> parent_name;

    // Team (null = workspace label)
    std::optional<std::string> team_id;
    std::optional<std::string> team_name;
};

void from_json(const json& j, IssueLabel& l);
```

**Table columns:** `name`, `color` (as colored block), `team_name` (or "Workspace"), `is_group`

### 2.8 Comment

```cpp
// src/modules/comments/model.h

struct Comment {
    std::string id;
    std::string created_at;
    std::string updated_at;

    std::string body;                         // Markdown content
    std::optional<std::string> edited_at;
    std::optional<std::string> resolved_at;
    std::string url;

    // Author
    std::optional<std::string> user_id;
    std::optional<std::string> user_name;

    // Parent (for threaded comments)
    std::optional<std::string> parent_id;

    // Target
    std::optional<std::string> issue_id;
    std::optional<std::string> project_update_id;
};

void from_json(const json& j, Comment& c);
```

**Table columns:** `user_name`, `body` (truncated), `created_at`

**Detail view:** Full `body` in markdown

### 2.9 Document

```cpp
// src/modules/documents/model.h

struct Document {
    std::string id;
    std::string created_at;
    std::string updated_at;

    std::string title;
    std::optional<std::string> icon;
    std::optional<std::string> color;
    std::string slug_id;
    std::string url;
    std::optional<std::string> content;       // Markdown

    // Creator
    std::optional<std::string> creator_id;
    std::optional<std::string> creator_name;

    // Associations
    std::optional<std::string> project_id;
    std::optional<std::string> project_name;
    std::optional<std::string> initiative_id;

    bool trashed = false;
};

void from_json(const json& j, Document& d);
```

**Table columns:** `title`, `creator_name`, `project_name`, `updated_at`

### 2.10 Notification

```cpp
// src/modules/notifications/model.h

struct Notification {
    std::string id;
    std::string created_at;
    std::string updated_at;

    std::string type;
    std::optional<std::string> read_at;
    std::optional<std::string> snoozed_until_at;
    std::optional<std::string> archived_at;

    // Actor
    std::optional<std::string> actor_id;
    std::optional<std::string> actor_name;

    // Display fields (internal but useful for CLI)
    std::optional<std::string> title;
    std::optional<std::string> subtitle;
    std::optional<std::string> url;
};

void from_json(const json& j, Notification& n);
```

**Table columns:** `type`, `title`, `actor_name`, `created_at`, unread indicator

### 2.11 CustomView

```cpp
// src/modules/views/model.h

struct CustomView {
    std::string id;
    std::string created_at;
    std::string updated_at;

    std::string name;
    std::optional<std::string> description;
    std::optional<std::string> icon;
    std::optional<std::string> color;
    std::string slug_id;
    std::optional<std::string> model_name;
    bool shared = false;

    // Filter data stored as raw JSON for pass-through
    std::optional<json> filter_data;

    // Owner
    std::optional<std::string> owner_id;
    std::optional<std::string> owner_name;

    // Team
    std::optional<std::string> team_id;
    std::optional<std::string> team_name;
};

void from_json(const json& j, CustomView& v);
```

**Table columns:** `name`, `owner_name`, `shared`, `model_name`

### 2.12 Initiative

```cpp
// src/modules/initiatives/model.h

struct Initiative {
    std::string id;
    std::string created_at;
    std::string updated_at;

    std::string name;
    std::optional<std::string> description;
    std::optional<std::string> icon;
    std::optional<std::string> color;
    std::string slug_id;
    std::string url;

    std::optional<std::string> status;        // Planned, Active, Completed
    std::optional<std::string> health;        // onTrack, atRisk, offTrack
    std::optional<std::string> target_date;

    std::optional<std::string> owner_id;
    std::optional<std::string> owner_name;

    std::optional<std::string> started_at;
    std::optional<std::string> completed_at;

    bool trashed = false;
};

void from_json(const json& j, Initiative& i);
```

**Table columns:** `name`, `status`, `health`, `owner_name`, `target_date`

### 2.13 Attachment

```cpp
// src/modules/issues/attachment_model.h

struct Attachment {
    std::string id;
    std::string created_at;

    std::optional<std::string> title;
    std::optional<std::string> subtitle;
    std::optional<std::string> url;
    std::optional<std::string> source_type;

    std::optional<std::string> creator_id;
    std::optional<std::string> creator_name;

    std::optional<std::string> issue_id;
};

void from_json(const json& j, Attachment& a);
```

### 2.14 Favorite

```cpp
// src/modules/favorites/model.h

struct Favorite {
    std::string id;
    std::string created_at;

    std::string type;
    std::optional<std::string> folder_name;
    double sort_order = 0.0;

    // Referenced entity (one of these will be set)
    std::optional<std::string> issue_id;
    std::optional<std::string> project_id;
    std::optional<std::string> cycle_id;
    std::optional<std::string> custom_view_id;
    std::optional<std::string> document_id;
    std::optional<std::string> label_id;

    std::optional<std::string> url;
    std::optional<std::string> title;
};

void from_json(const json& j, Favorite& f);
```

### 2.15 WorkflowState

```cpp
// src/modules/teams/workflow_state_model.h

struct WorkflowState {
    std::string id;
    std::string created_at;

    std::string name;
    std::string color;
    std::optional<std::string> description;
    double position = 0.0;
    std::string type;                         // triage, backlog, unstarted, started, completed, canceled

    std::optional<std::string> team_id;
    std::optional<std::string> team_name;
};

void from_json(const json& j, WorkflowState& ws);
```

**Table columns:** `name`, `type`, `color` (visual block), `position`

### 2.16 IssueRelation

```cpp
// src/modules/issues/relation_model.h

struct IssueRelation {
    std::string id;
    std::string created_at;

    std::string type;                         // blocks, duplicate, related, similar

    std::optional<std::string> issue_id;
    std::optional<std::string> issue_identifier;

    std::optional<std::string> related_issue_id;
    std::optional<std::string> related_issue_identifier;
};

void from_json(const json& j, IssueRelation& r);
```

### 2.17 Webhook

```cpp
// src/modules/webhooks/model.h

struct Webhook {
    std::string id;
    std::string created_at;
    std::string updated_at;

    std::optional<std::string> label;
    std::optional<std::string> url;
    bool enabled = true;

    std::optional<std::string> team_id;
    std::optional<std::string> creator_id;
    std::optional<std::string> creator_name;
};

void from_json(const json& j, Webhook& w);
```

### 2.18 Organization

```cpp
// src/modules/organization/model.h

struct Organization {
    std::string id;
    std::string created_at;

    std::string name;
    std::string url_key;
    std::optional<std::string> logo_url;
    int user_count = 0;
    int created_issue_count = 0;

    std::optional<std::string> git_branch_format;
    bool git_linkback_messages_enabled = false;
    bool saml_enabled = false;
    bool scim_enabled = false;

    std::optional<std::string> trial_ends_at;

    // Subscription info
    std::optional<std::string> subscription_type;
};

void from_json(const json& j, Organization& o);
```

### 2.19 ProjectMilestone

```cpp
// src/modules/projects/milestone_model.h

struct ProjectMilestone {
    std::string id;
    std::string created_at;
    std::string updated_at;

    std::string name;
    std::optional<std::string> description;
    std::optional<std::string> target_date;
    std::string status;                       // unstarted, next, overdue, done
    double progress = 0.0;
    double sort_order = 0.0;

    std::optional<std::string> project_id;
    std::optional<std::string> project_name;
};

void from_json(const json& j, ProjectMilestone& m);
```

### 2.20 ProjectUpdate

```cpp
// src/modules/projects/update_model.h

struct ProjectUpdate {
    std::string id;
    std::string created_at;
    std::string updated_at;

    std::string body;                         // Markdown
    std::optional<std::string> health;        // onTrack, atRisk, offTrack
    std::string url;
    std::string slug_id;

    std::optional<std::string> user_id;
    std::optional<std::string> user_name;

    std::optional<std::string> project_id;
    std::optional<std::string> project_name;

    std::optional<std::string> diff_markdown;
};

void from_json(const json& j, ProjectUpdate& u);
```

### 2.21 Integration

```cpp
// src/modules/integrations/model.h

struct Integration {
    std::string id;
    std::string created_at;

    std::string service;

    std::optional<std::string> team_id;
    std::optional<std::string> team_name;

    std::optional<std::string> creator_id;
    std::optional<std::string> creator_name;
};

void from_json(const json& j, Integration& i);
```

**Table columns:** `service`, `team_name`, `creator_name`, `created_at`

---

## 3. Module Architecture

### 3.1 Directory Structure

```
src/
  main.cpp                          — Entry point, CLI11 app setup, command registration
  core/
    types.h                         — Common types (PageInfo, Connection<T>)
    http_client.h / http_client.cpp — libcurl wrapper for GraphQL POST
    graphql.h / graphql.cpp         — GraphQL query builder, variable injection
    auth.h / auth.cpp               — API key loading (env var, config file)
    config.h / config.cpp           — TOML config management (~/.config/lin/)
    output.h / output.cpp           — Table renderer, detail view, JSON output
    color.h / color.cpp             — ANSI color support, pipe detection
    paginator.h / paginator.cpp     — Cursor-based pagination helper
    filter.h / filter.cpp           — CLI flags → GraphQL filter input builder
    error.h / error.cpp             — Error types, GraphQL error parsing, retry
    cache.h / cache.cpp             — SQLite cache layer (Phase 6)
  modules/
    issues/
      model.h                       — Issue, IssueRelation, Attachment structs
      api.h / api.cpp               — GraphQL queries/mutations, response parsing
      commands.h / commands.cpp      — CLI command handlers (list, create, update, etc.)
    projects/
      model.h                       — Project, ProjectMilestone, ProjectUpdate structs
      api.h / api.cpp
      commands.h / commands.cpp
    teams/
      model.h                       — Team, WorkflowState structs
      api.h / api.cpp
      commands.h / commands.cpp
    cycles/
      model.h                       — Cycle struct
      api.h / api.cpp
      commands.h / commands.cpp
    users/
      model.h                       — User struct
      api.h / api.cpp
      commands.h / commands.cpp
    labels/
      model.h                       — IssueLabel struct
      api.h / api.cpp
      commands.h / commands.cpp
    comments/
      model.h                       — Comment struct
      api.h / api.cpp
      commands.h / commands.cpp
    documents/
      model.h                       — Document struct
      api.h / api.cpp
      commands.h / commands.cpp
    favorites/
      model.h                       — Favorite struct
      api.h / api.cpp
      commands.h / commands.cpp
    notifications/
      model.h                       — Notification struct
      api.h / api.cpp
      commands.h / commands.cpp
    webhooks/
      model.h                       — Webhook struct
      api.h / api.cpp
      commands.h / commands.cpp
    views/
      model.h                       — CustomView struct
      api.h / api.cpp
      commands.h / commands.cpp
    initiatives/
      model.h                       — Initiative struct
      api.h / api.cpp
      commands.h / commands.cpp
    search/
      api.h / api.cpp               — Search queries (issues, projects, docs, semantic)
      commands.h / commands.cpp
    organization/
      model.h                       — Organization struct
      api.h / api.cpp
      commands.h / commands.cpp
    integrations/
      model.h                       — Integration struct
      api.h / api.cpp
      commands.h / commands.cpp
  tui/                              — Phase 5: FTXUI-based TUI
    app.h / app.cpp
    kanban.h / kanban.cpp
    issue_detail.h / issue_detail.cpp
```

### 3.2 Module Pattern

Each module follows the same pattern:

**model.h** — Data structs + JSON parsing (`from_json`)
```cpp
// Pure data, no dependencies on other modules
struct MyEntity { ... };
void from_json(const json& j, MyEntity& e);
```

**api.h / api.cpp** — GraphQL queries + HTTP calls + response parsing
```cpp
// Depends on: core/http_client, core/graphql, model.h
Connection<MyEntity> list_entities(const ListOptions& opts);
MyEntity get_entity(const std::string& id);
MyEntity create_entity(const CreateInput& input);
MyEntity update_entity(const std::string& id, const UpdateInput& input);
void delete_entity(const std::string& id);
```

**commands.h / commands.cpp** — CLI11 subcommand registration + handler functions
```cpp
// Depends on: api.h, core/output, core/filter
void register_commands(CLI::App& app);
// Each handler: parse CLI args → call api → format output
```

---

## 4. Core Infrastructure

### 4.1 HTTP Client

**Library:** libcurl (widely available, C-native, handles HTTPS, proxy, timeouts)

```cpp
// src/core/http_client.h

struct HttpResponse {
    long status_code;
    std::string body;
    std::string error_message;
};

class HttpClient {
public:
    HttpClient();
    ~HttpClient();

    // Non-copyable (owns CURL handle)
    HttpClient(const HttpClient&) = delete;
    HttpClient& operator=(const HttpClient&) = delete;

    // All GraphQL goes through this
    HttpResponse post(
        const std::string& url,
        const std::string& body,
        const std::vector<std::pair<std::string, std::string>>& headers
    );

    void set_timeout(long timeout_ms);

private:
    CURL* curl_handle_;
};
```

**Endpoint:** `https://api.linear.app/graphql`

**Headers:**
- `Content-Type: application/json`
- `Authorization: <api_key>` (Linear uses bare API key, not `Bearer`)

### 4.2 JSON Parsing

**Library:** nlohmann/json

**Justification over rapidjson:**
- Header-only, trivial to integrate via CMake FetchContent
- Idiomatic C++ (operator overloads, ADL `from_json`/`to_json`)
- `std::optional` support out of the box
- Better error messages for debugging
- Performance is sufficient (we process API responses, not streaming data)
- rapidjson would be faster but adds complexity with its DOM-based API

**Parsing approach:**
- Each model struct implements a free `from_json(const json& j, T& val)` function
- Use `.value()` with defaults for optional fields
- Use `.at()` for required fields (throws on missing)
- Nested objects (e.g., `issue.team.name`) are flattened into the struct

```cpp
// Example pattern
void from_json(const json& j, Issue& i) {
    j.at("id").get_to(i.id);
    j.at("title").get_to(i.title);
    j.at("identifier").get_to(i.identifier);
    i.priority = j.value("priority", 0.0);
    i.priority_label = j.value("priorityLabel", "");
    i.description = j.contains("description") && !j["description"].is_null()
        ? std::optional<std::string>(j["description"].get<std::string>())
        : std::nullopt;

    // Flatten nested objects
    if (j.contains("assignee") && !j["assignee"].is_null()) {
        i.assignee_id = j["assignee"].value("id", "");
        i.assignee_name = j["assignee"].value("displayName", "");
    }

    if (j.contains("state") && !j["state"].is_null()) {
        i.state_id = j["state"].value("id", "");
        i.state_name = j["state"].value("name", "");
        i.state_type = j["state"].value("type", "");
    }
}
```

### 4.3 GraphQL Query Builder

```cpp
// src/core/graphql.h

struct GraphQLRequest {
    std::string query;
    json variables;
};

// Build a GraphQL POST body
std::string build_request_body(const GraphQLRequest& request);

// Parse a GraphQL response, extracting data or throwing on errors
json parse_response(const std::string& response_body);
```

GraphQL queries are stored as string constants in each module's `api.cpp`:

```cpp
// Example: src/modules/issues/api.cpp
static const std::string ISSUES_LIST_QUERY = R"(
query IssuesList($first: Int, $after: String, $filter: IssueFilter, $orderBy: PaginationOrderBy) {
    issues(first: $first, after: $after, filter: $filter, orderBy: $orderBy) {
        nodes {
            id
            identifier
            title
            priority
            priorityLabel
            dueDate
            url
            branchName
            state { id name type color }
            assignee { id displayName }
            team { id name key }
            labels { nodes { id name color } }
            project { id name }
            cycle { id number }
        }
        pageInfo {
            hasNextPage
            endCursor
        }
    }
}
)";
```

### 4.4 Authentication

**Priority order:**
1. `LINEAR_API_KEY` environment variable
2. `~/.config/lin/config.toml` → `api_key` field
3. Error with instructions to set up

```cpp
// src/core/auth.h

// Returns the API key or throws with setup instructions
std::string get_api_key();

// Validate the API key by calling viewer() query
bool validate_api_key(const std::string& key);
```

**`lin config init`** — Interactive setup that prompts for API key and writes config file.

### 4.5 Output Formatting

```cpp
// src/core/output.h

enum class OutputFormat {
    Table,    // Default: aligned columns
    Detail,   // Single-entity detailed view
    Json,     // Raw JSON (--json flag)
    Csv       // CSV for piping (--csv flag)
};

struct TableColumn {
    std::string header;
    int min_width;
    int max_width;
    bool right_align = false;
    // Optional color function based on value
};

class TableRenderer {
public:
    TableRenderer(const std::vector<TableColumn>& columns);

    void add_row(const std::vector<std::string>& values);
    void render(std::ostream& out) const;

private:
    // Column width calculation (respect terminal width)
    // Truncation with "..." for long values
    // UTF-8 aware width calculation
};

class DetailRenderer {
public:
    void add_field(const std::string& label, const std::string& value);
    void add_section(const std::string& title);
    void add_markdown(const std::string& content);
    void render(std::ostream& out) const;
};

// Global output format (set by --json or --csv flags)
OutputFormat get_output_format();
void set_output_format(OutputFormat fmt);
```

**Features:**
- Auto-detect terminal width via `ioctl(TIOCGWINSZ)` or `$COLUMNS`
- Truncate long columns with `...`
- No color when piped (`isatty(STDOUT_FILENO)` check)
- Priority coloring: Urgent=red, High=orange, Normal=default, Low=gray
- State type coloring: started=yellow, completed=green, canceled=gray

### 4.6 Color Support

```cpp
// src/core/color.h

namespace color {

bool enabled();  // false when piped or --no-color

std::string red(const std::string& s);
std::string green(const std::string& s);
std::string yellow(const std::string& s);
std::string blue(const std::string& s);
std::string magenta(const std::string& s);
std::string cyan(const std::string& s);
std::string gray(const std::string& s);
std::string bold(const std::string& s);
std::string dim(const std::string& s);

// Color from hex string (for labels, teams)
std::string from_hex(const std::string& hex, const std::string& s);

} // namespace color
```

**Detection logic:**
1. `--no-color` flag → disable
2. `NO_COLOR` env var → disable (respects [no-color.org](https://no-color.org))
3. `!isatty(STDOUT_FILENO)` → disable
4. Otherwise → enable

### 4.7 Pagination

Linear uses Relay-style cursor pagination with `nodes`, `edges`, `pageInfo`.

```cpp
// src/core/paginator.h

struct PaginationOptions {
    int first = 50;                   // Items per page (Linear max: 250)
    std::optional<std::string> after; // Cursor for next page
    bool fetch_all = false;           // --all flag: auto-paginate everything
};

// Generic paginator that handles cursor iteration
template<typename T>
class Paginator {
public:
    using FetchFn = std::function<Connection<T>(const PaginationOptions&)>;

    Paginator(FetchFn fetch, PaginationOptions opts);

    // Fetch next page
    std::optional<Connection<T>> next();

    // Fetch all pages (respects --all or --limit)
    std::vector<T> fetch_all();

    bool has_next() const;

private:
    FetchFn fetch_fn_;
    PaginationOptions opts_;
    bool has_more_ = true;
};
```

### 4.8 Filtering

Translate CLI flags into Linear's GraphQL filter input types.

```cpp
// src/core/filter.h

// Builds an IssueFilter JSON object from CLI flags
json build_issue_filter(
    const std::optional<std::string>& team,        // --team
    const std::optional<std::string>& assignee,    // --assignee, --me
    const std::optional<std::string>& state,       // --state
    const std::optional<std::string>& priority,    // --priority
    const std::optional<std::string>& label,       // --label
    const std::optional<std::string>& project,     // --project
    const std::optional<std::string>& cycle,       // --cycle
    const std::optional<std::string>& creator       // --creator
);

// Builds a ProjectFilter JSON object from CLI flags
json build_project_filter(
    const std::optional<std::string>& status,
    const std::optional<std::string>& lead,
    const std::optional<std::string>& health
);

// Builds a CycleFilter JSON object from CLI flags
json build_cycle_filter(
    const std::optional<std::string>& team,
    bool active_only
);
```

**Filter value resolution:** Team names/keys, user display names, label names, and state names are resolved to IDs before building the filter. This uses the cache (Phase 6) or a lookup query.

### 4.9 Error Handling

```cpp
// src/core/error.h

enum class ErrorKind {
    Network,          // Connection failed, timeout
    Auth,             // 401, invalid API key
    NotFound,         // 404 or null result
    RateLimit,        // 429, includes retry-after
    GraphQL,          // GraphQL errors array in response
    Validation,       // Invalid input
    Internal          // Unexpected errors
};

class LinError : public std::runtime_error {
public:
    LinError(ErrorKind kind, const std::string& message);

    ErrorKind kind() const;
    // For rate limits: seconds until retry
    std::optional<int> retry_after() const;
};

// Parse GraphQL errors from response
void check_graphql_errors(const json& response);

// Retry wrapper for rate-limited requests
template<typename F>
auto with_retry(F&& fn, int max_retries = 3) -> decltype(fn());
```

**Rate limiting strategy:**
1. Catch 429 responses
2. Read `Retry-After` header or `extensions.rateLimit` from response
3. Wait and retry (up to 3 attempts)
4. Exponential backoff: 1s, 2s, 4s

### 4.10 Configuration

**Library:** toml++ (header-only, C++17, spec-compliant TOML parser)

**Config file:** `~/.config/lin/config.toml`

```toml
# API authentication
api_key = "lin_api_xxxxxxxxxx"

# Default workspace behavior
[defaults]
team = "ENG"             # Default team key for commands
output = "table"         # table | json | csv

# Display preferences
[display]
color = true             # Enable/disable colors
page_size = 50           # Default items per page
date_format = "relative" # relative | iso | short
```

```cpp
// src/core/config.h

struct Config {
    std::string api_key;

    struct Defaults {
        std::optional<std::string> team;
        std::string output = "table";
    } defaults;

    struct Display {
        bool color = true;
        int page_size = 50;
        std::string date_format = "relative";
    } display;
};

Config load_config();
void save_config(const Config& config);
std::string config_path();  // ~/.config/lin/config.toml
```

### 4.11 Cache (Phase 6)

**Library:** SQLite3

**Purpose:** Cache slow-changing reference data to avoid repeated API calls for team/user/label/state lookups during filtering.

```cpp
// src/core/cache.h

class Cache {
public:
    Cache();  // Opens/creates ~/.config/lin/cache.db

    // Teams
    void store_teams(const std::vector<Team>& teams);
    std::optional<Team> find_team_by_key(const std::string& key);
    std::optional<Team> find_team_by_name(const std::string& name);

    // Users
    void store_users(const std::vector<User>& users);
    std::optional<User> find_user_by_name(const std::string& display_name);

    // Labels
    void store_labels(const std::vector<IssueLabel>& labels);
    std::optional<IssueLabel> find_label_by_name(const std::string& name);

    // Workflow States
    void store_states(const std::vector<WorkflowState>& states);
    std::optional<WorkflowState> find_state_by_name(
        const std::string& team_id,
        const std::string& name
    );

    // Cache invalidation
    void invalidate_all();
    void invalidate(const std::string& table);
    bool is_stale(const std::string& table, int max_age_minutes = 60);

private:
    sqlite3* db_;
};
```

**Cache TTL:** 60 minutes for teams, users, labels, states. Invalidated on `lin cache clear`.

---

## 5. CLI Command Tree

Every command with full syntax, GraphQL mapping, output format, and example.

### 5.0 Global Flags

```
lin [--json] [--csv] [--no-color] [--verbose] [--team <key>] <command> [subcommand] [args]

Global flags:
  --json          Output raw JSON instead of table
  --csv           Output CSV (for piping to other tools)
  --no-color      Disable ANSI colors
  --verbose       Show debug info (HTTP requests, timings)
  --team <key>    Override default team (e.g., --team ENG)
```

---

### 5.1 Issues

#### `lin issues list`

```
lin issues list [flags]

Flags:
  --team <key>           Filter by team key (e.g., ENG)
  --assignee <name>      Filter by assignee display name
  --me                   Filter to issues assigned to me
  --state <name>         Filter by workflow state name (e.g., "In Progress")
  --state-type <type>    Filter by state type (triage|backlog|unstarted|started|completed|canceled)
  --priority <level>     Filter by priority (none|urgent|high|normal|low)
  --label <name>         Filter by label name
  --project <name>       Filter by project name
  --cycle <number>       Filter by cycle number ("current" for active cycle)
  --creator <name>       Filter by creator
  --include-archived     Include archived issues
  --all                  Fetch all pages (default: first 50)
  --limit <n>            Max issues to return
  --sort <field>         Sort by field (created|updated|priority)
  --order <dir>          Sort direction (asc|desc)

GraphQL: issues(filter: IssueFilter, first, after, orderBy, sort)
Table columns: IDENTIFIER | PRIORITY | TITLE | STATE | ASSIGNEE | DUE DATE
```

**Example:**
```bash
lin issues list --team ENG --me --state-type started
lin issues list --priority urgent --all --json
lin issues list --label "Bug" --project "Q1 Launch"
```

#### `lin issues show <identifier>`

```
lin issues show <identifier>

Args:
  <identifier>     Issue identifier (e.g., ENG-123) or UUID

GraphQL: issue(id)
Output: Detail view with all fields
```

**Example:**
```bash
lin issues show ENG-123
lin issues show ENG-123 --json
```

#### `lin issues create`

```
lin issues create [flags]

Flags:
  --title <text>         Issue title (required)
  --team <key>           Team key (required, or use default)
  --description <text>   Description (markdown)
  --desc-file <path>     Read description from file
  --assignee <name>      Assign to user
  --priority <level>     Priority: none|urgent|high|normal|low (default: none)
  --state <name>         Initial workflow state
  --label <name>         Add label (repeatable)
  --project <name>       Associate with project
  --cycle <number>       Add to cycle ("current" for active)
  --parent <identifier>  Set parent issue
  --estimate <points>    Estimation points
  --due-date <date>      Due date (YYYY-MM-DD)

GraphQL: issueCreate(input: IssueCreateInput)
Output: Created issue detail
```

**Example:**
```bash
lin issues create --title "Fix login bug" --team ENG --priority high --label Bug --assignee "Jane Doe"
lin issues create --title "Refactor auth" --team ENG --desc-file ./description.md
```

#### `lin issues update <identifier>`

```
lin issues update <identifier> [flags]

Args:
  <identifier>     Issue identifier (e.g., ENG-123)

Flags:
  --title <text>         Update title
  --description <text>   Update description
  --assignee <name>      Reassign (use "" to unassign)
  --priority <level>     Change priority
  --state <name>         Change workflow state
  --project <name>       Move to project (use "" to remove)
  --cycle <number>       Move to cycle
  --parent <identifier>  Set parent (use "" to remove)
  --estimate <points>    Set estimate
  --due-date <date>      Set due date (use "" to clear)

GraphQL: issueUpdate(input: IssueUpdateInput, id)
Output: Updated issue detail
```

**Example:**
```bash
lin issues update ENG-123 --state "In Review" --priority normal
lin issues update ENG-123 --assignee "John Smith" --due-date 2026-03-15
```

#### `lin issues delete <identifier>`

```
lin issues delete <identifier> [flags]

Flags:
  --permanent    Permanently delete (not just trash)
  --yes          Skip confirmation prompt

GraphQL: issueDelete(id, permanentlyDelete)
Output: Confirmation message
```

#### `lin issues archive <identifier>`

```
lin issues archive <identifier>

GraphQL: issueArchive(id)
Output: Confirmation message
```

#### `lin issues unarchive <identifier>`

```
lin issues unarchive <identifier>

GraphQL: issueUnarchive(id)
Output: Confirmation message
```

#### `lin issues search <query>`

```
lin issues search <query> [flags]

Args:
  <query>          Search text

Flags:
  --team <key>           Scope to team
  --include-comments     Search in comments too
  --include-archived     Include archived issues
  --limit <n>            Max results (default: 20)

GraphQL: searchIssues(term, filter, includeComments, teamId)
Table columns: IDENTIFIER | PRIORITY | TITLE | STATE | ASSIGNEE
```

**Example:**
```bash
lin issues search "authentication error" --team ENG
```

#### `lin issues assign <identifier> <assignee>`

```
lin issues assign <identifier> <assignee>

GraphQL: issueUpdate(id, input: { assigneeId })
Output: Confirmation message
```

**Example:**
```bash
lin issues assign ENG-123 "Jane Doe"
lin issues assign ENG-123 --me
```

#### `lin issues label add <identifier> <label_name>`

```
lin issues label add <identifier> <label_name>

GraphQL: issueAddLabel(id, labelId)
Output: Confirmation message
```

#### `lin issues label remove <identifier> <label_name>`

```
lin issues label remove <identifier> <label_name>

GraphQL: issueRemoveLabel(id, labelId)
Output: Confirmation message
```

#### `lin issues move <identifier> --state <state_name>`

```
lin issues move <identifier> --state <state_name>

GraphQL: issueUpdate(id, input: { stateId })
Output: Confirmation message
```

**Example:**
```bash
lin issues move ENG-123 --state "In Progress"
```

#### `lin issues relate <identifier> <related_identifier> [--type <type>]`

```
lin issues relate <identifier> <related_identifier> [flags]

Flags:
  --type <type>    Relation type: blocks|duplicate|related|similar (default: related)

GraphQL: issueRelationCreate(input: IssueRelationCreateInput)
Output: Confirmation message
```

#### `lin issues unrelate <relation_id>`

```
lin issues unrelate <relation_id>

GraphQL: issueRelationDelete(id)
Output: Confirmation message
```

#### `lin issues attach <identifier> --url <url>`

```
lin issues attach <identifier> --url <url> [flags]

Flags:
  --title <text>    Attachment title
  --url <url>       URL to attach

GraphQL: attachmentLinkURL(url, issueId, title)
Output: Confirmation message
```

#### `lin issues detach <attachment_id>`

```
lin issues detach <attachment_id>

GraphQL: attachmentDelete(id)
Output: Confirmation message
```

#### `lin issues subscribe <identifier>`

```
lin issues subscribe <identifier>

GraphQL: issueSubscribe(id)
Output: Confirmation message
```

#### `lin issues unsubscribe <identifier>`

```
lin issues unsubscribe <identifier>

GraphQL: issueUnsubscribe(id)
Output: Confirmation message
```

#### `lin issues branch <identifier>`

```
lin issues branch <identifier>

GraphQL: issue(id) → branchName field
Output: Prints suggested branch name
```

**Example:**
```bash
git checkout -b $(lin issues branch ENG-123)
```

#### `lin issues bulk update`

```
lin issues bulk update <id1> <id2> ... [flags]

Flags:
  --state <name>       Move all to state
  --assignee <name>    Assign all to user
  --priority <level>   Set priority on all
  --label <name>       Add label to all
  --project <name>     Move all to project

GraphQL: issueBatchUpdate(ids, input: IssueUpdateInput)
Output: Count of updated issues
```

---

### 5.2 Projects

#### `lin projects list`

```
lin projects list [flags]

Flags:
  --status <type>       Filter by status (backlog|planned|started|paused|completed|canceled)
  --lead <name>         Filter by project lead
  --health <type>       Filter by health (onTrack|atRisk|offTrack)
  --include-archived    Include archived
  --all                 Fetch all pages
  --limit <n>           Max results

GraphQL: projects(filter: ProjectFilter, first, after)
Table columns: NAME | STATUS | HEALTH | LEAD | PROGRESS | TARGET DATE
```

#### `lin projects show <id>`

```
lin projects show <id_or_slug>

GraphQL: project(id)
Output: Detail view with description, milestones, members, progress
```

#### `lin projects create`

```
lin projects create [flags]

Flags:
  --name <text>          Project name (required)
  --description <text>   Description
  --lead <name>          Project lead
  --status <type>        Initial status
  --start-date <date>    Start date (YYYY-MM-DD)
  --target-date <date>   Target date (YYYY-MM-DD)
  --priority <level>     Priority: none|urgent|high|normal|low
  --team <key>           Associate with team (repeatable)

GraphQL: projectCreate(input: ProjectCreateInput)
Output: Created project detail
```

#### `lin projects update <id>`

```
lin projects update <id> [flags]

Flags:
  --name <text>          Update name
  --description <text>   Update description
  --lead <name>          Change lead
  --status <type>        Change status
  --start-date <date>    Set start date
  --target-date <date>   Set target date
  --priority <level>     Set priority

GraphQL: projectUpdate(input: ProjectUpdateInput, id)
```

#### `lin projects delete <id>`

```
lin projects delete <id> [--yes]

GraphQL: projectDelete(id)
```

#### `lin projects search <query>`

```
lin projects search <query> [flags]

Flags:
  --include-comments     Include comments
  --limit <n>            Max results

GraphQL: searchProjects(term)
```

#### `lin projects milestones <project_id>`

```
lin projects milestones <project_id>

GraphQL: project(id) → projectMilestones
Table columns: NAME | STATUS | TARGET DATE | PROGRESS
```

#### `lin projects milestones create`

```
lin projects milestones create --project <id> [flags]

Flags:
  --name <text>          Milestone name (required)
  --project <id>         Project ID (required)
  --description <text>   Description
  --target-date <date>   Target date

GraphQL: projectMilestoneCreate(input)
```

#### `lin projects milestones update <id>`

```
lin projects milestones update <id> [flags]

Flags:
  --name <text>          Update name
  --description <text>   Update description
  --target-date <date>   Set target date

GraphQL: projectMilestoneUpdate(input, id)
```

#### `lin projects milestones delete <id>`

```
lin projects milestones delete <id> [--yes]

GraphQL: projectMilestoneDelete(id)
```

#### `lin projects updates <project_id>`

```
lin projects updates <project_id>

GraphQL: project(id) → projectUpdates (or projectUpdates query with filter)
Table columns: HEALTH | USER | DATE | BODY (truncated)
```

#### `lin projects updates create <project_id>`

```
lin projects updates create <project_id> [flags]

Flags:
  --body <text>          Update content (markdown)
  --body-file <path>     Read body from file
  --health <type>        Health: onTrack|atRisk|offTrack (required)

GraphQL: projectUpdateCreate(input: ProjectUpdateCreateInput)
```

#### `lin projects members <project_id>`

```
lin projects members <project_id>

GraphQL: project(id) → members
Table columns: NAME | EMAIL | ROLE
```

---

### 5.3 Teams

#### `lin teams list`

```
lin teams list [flags]

Flags:
  --include-archived    Include archived teams

GraphQL: teams(filter)
Table columns: KEY | NAME | ISSUES | CYCLES | TRIAGE
```

#### `lin teams show <id_or_key>`

```
lin teams show <id_or_key>

GraphQL: team(id)
Output: Detail view with settings, active cycle, issue counts
```

#### `lin teams members <id_or_key>`

```
lin teams members <id_or_key>

GraphQL: team(id) → members
Table columns: NAME | EMAIL | ROLE | ACTIVE
```

#### `lin teams states <id_or_key>`

```
lin teams states <id_or_key>

GraphQL: team(id) → states (or workflowStates with team filter)
Table columns: NAME | TYPE | COLOR | POSITION
```

#### `lin teams labels <id_or_key>`

```
lin teams labels <id_or_key>

GraphQL: team(id) → labels
Table columns: NAME | COLOR | GROUP
```

#### `lin teams cycles <id_or_key>`

```
lin teams cycles <id_or_key>

GraphQL: team(id) → cycles
Table columns: NUMBER | NAME | START | END | PROGRESS | ACTIVE
```

---

### 5.4 Cycles

#### `lin cycles list`

```
lin cycles list [flags]

Flags:
  --team <key>     Filter by team (required or use default)
  --active         Show only active cycle
  --upcoming       Show upcoming cycles
  --past           Show past cycles

GraphQL: cycles(filter: CycleFilter)
Table columns: NUMBER | NAME | START | END | PROGRESS | STATUS
```

#### `lin cycles show <id>`

```
lin cycles show <id>

GraphQL: cycle(id)
Output: Detail view with issues, progress, dates
```

#### `lin cycles current [--team <key>]`

```
lin cycles current [--team <key>]

GraphQL: team(id) → activeCycle
Output: Active cycle detail, or "No active cycle" message
```

#### `lin cycles create`

```
lin cycles create [flags]

Flags:
  --team <key>         Team (required)
  --name <text>        Cycle name
  --starts-at <date>   Start date (required)
  --ends-at <date>     End date (required)
  --description <text> Description

GraphQL: cycleCreate(input: CycleCreateInput)
```

#### `lin cycles update <id>`

```
lin cycles update <id> [flags]

Flags:
  --name <text>        Update name
  --starts-at <date>   Update start date
  --ends-at <date>     Update end date
  --description <text> Update description

GraphQL: cycleUpdate(input: CycleUpdateInput, id)
```

#### `lin cycles archive <id>`

```
lin cycles archive <id>

GraphQL: cycleArchive(id)
```

#### `lin cycles issues <id>`

```
lin cycles issues <id>

GraphQL: cycle(id) → issues
Table columns: IDENTIFIER | PRIORITY | TITLE | STATE | ASSIGNEE
```

---

### 5.5 Users

#### `lin users list`

```
lin users list [flags]

Flags:
  --include-disabled    Include suspended users
  --all                 Fetch all pages

GraphQL: users(filter, includeDisabled)
Table columns: NAME | EMAIL | ACTIVE | ADMIN
```

#### `lin users show <id_or_name>`

```
lin users show <id_or_name>

GraphQL: user(id)
Output: Detail view with status, teams, assigned issues count
```

---

### 5.6 `lin me`

```
lin me [flags]

Flags:
  --issues         Show my assigned issues
  --notifications  Show my unread notifications

GraphQL: viewer() (+ assignedIssues, notifications subqueries)
Output: Current user detail, optionally with assigned issues and notifications
```

**Example:**
```bash
lin me
lin me --issues
lin me --notifications
```

---

### 5.7 Labels

#### `lin labels list`

```
lin labels list [flags]

Flags:
  --team <key>     Filter by team (omit for workspace labels)
  --group          Show only group labels
  --all            Fetch all pages

GraphQL: issueLabels(filter: IssueLabelFilter)
Table columns: NAME | COLOR | TEAM | GROUP
```

#### `lin labels show <id_or_name>`

```
lin labels show <id_or_name>

GraphQL: issueLabel(id)
Output: Detail view
```

#### `lin labels create`

```
lin labels create [flags]

Flags:
  --name <text>        Label name (required)
  --color <hex>        Color hex (required, e.g., "#FF0000")
  --team <key>         Team (omit for workspace label)
  --description <text> Description
  --parent <name>      Parent label (for grouped labels)

GraphQL: issueLabelCreate(input: IssueLabelCreateInput)
```

#### `lin labels update <id>`

```
lin labels update <id> [flags]

Flags:
  --name <text>        Update name
  --color <hex>        Update color
  --description <text> Update description

GraphQL: issueLabelUpdate(input, id)
```

#### `lin labels delete <id>`

```
lin labels delete <id> [--yes]

GraphQL: issueLabelDelete(id)
```

---

### 5.8 Comments

#### `lin comments list --issue <identifier>`

```
lin comments list --issue <identifier> [flags]

Flags:
  --issue <identifier>   Issue to list comments for (required)
  --all                  Fetch all comments

GraphQL: issue(id) → comments (or comments(filter: {issue: {id: {eq: ...}}}))
Table columns: AUTHOR | DATE | BODY (truncated)
```

#### `lin comments show <id>`

```
lin comments show <id>

GraphQL: comment(id)
Output: Full comment body (rendered markdown)
```

#### `lin comments create`

```
lin comments create --issue <identifier> [flags]

Flags:
  --issue <identifier>   Target issue (required)
  --body <text>          Comment body (markdown)
  --body-file <path>     Read body from file

GraphQL: commentCreate(input: CommentCreateInput)
```

#### `lin comments update <id>`

```
lin comments update <id> --body <text>

GraphQL: commentUpdate(input, id)
```

#### `lin comments delete <id>`

```
lin comments delete <id> [--yes]

GraphQL: commentDelete(id)
```

---

### 5.9 Documents

#### `lin docs list`

```
lin docs list [flags]

Flags:
  --project <name>     Filter by project
  --all                Fetch all pages

GraphQL: documents(filter: DocumentFilter)
Table columns: TITLE | CREATOR | PROJECT | UPDATED
```

#### `lin docs show <id>`

```
lin docs show <id>

GraphQL: document(id)
Output: Full document content (rendered markdown)
```

#### `lin docs search <query>`

```
lin docs search <query> [flags]

Flags:
  --team <key>           Scope to team
  --include-comments     Search in comments
  --limit <n>            Max results

GraphQL: searchDocuments(term, teamId, includeComments)
Table columns: TITLE | CREATOR | PROJECT
```

#### `lin docs create`

```
lin docs create [flags]

Flags:
  --title <text>         Title (required)
  --content <text>       Content (markdown)
  --content-file <path>  Read content from file
  --project <id>         Associate with project

GraphQL: documentCreate(input: DocumentCreateInput)
```

#### `lin docs update <id>`

```
lin docs update <id> [flags]

Flags:
  --title <text>         Update title
  --content <text>       Update content
  --content-file <path>  Read content from file

GraphQL: documentUpdate(input, id)
```

#### `lin docs delete <id>`

```
lin docs delete <id> [--yes]

GraphQL: documentDelete(id)
```

---

### 5.10 Custom Views

#### `lin views list`

```
lin views list [flags]

Flags:
  --shared         Only shared views
  --all            Fetch all pages

GraphQL: customViews(filter: CustomViewFilter)
Table columns: NAME | OWNER | SHARED | MODEL
```

#### `lin views show <id>`

```
lin views show <id>

GraphQL: customView(id)
Output: View detail with filter configuration
```

#### `lin views create`

```
lin views create [flags]

Flags:
  --name <text>       View name (required)
  --description <text> Description
  --shared            Make shared with organization
  --filter <json>     Raw filter JSON (for advanced users)

GraphQL: customViewCreate(input: CustomViewCreateInput)
```

#### `lin views delete <id>`

```
lin views delete <id> [--yes]

GraphQL: customViewDelete(id)
```

---

### 5.11 Notifications

#### `lin notifications list`

```
lin notifications list [flags]

Flags:
  --unread         Only unread notifications
  --all            Fetch all pages
  --limit <n>      Max results

GraphQL: notifications(filter: NotificationFilter)
Table columns: [*] | TYPE | TITLE | ACTOR | DATE
(* = unread indicator)
```

#### `lin notifications show <id>`

```
lin notifications show <id>

GraphQL: notification(id)
Output: Notification detail with URL
```

#### `lin notifications count`

```
lin notifications count

GraphQL: notificationsUnreadCount()
Output: Single number (unread count)
```

#### `lin notifications read <id>`

```
lin notifications read <id>
lin notifications read --all

GraphQL: notificationUpdate(input: {readAt: now}, id) or notificationMarkReadAll(readAt, input)
```

#### `lin notifications archive <id>`

```
lin notifications archive <id>

GraphQL: notificationArchive(id)
```

#### `lin notifications snooze <id> --until <datetime>`

```
lin notifications snooze <id> --until <datetime>

GraphQL: notificationSnoozeAll(snoozedUntilAt, input)
```

---

### 5.12 Favorites

#### `lin favorites list`

```
lin favorites list

GraphQL: favorites()
Table columns: TYPE | TITLE | URL
```

#### `lin favorites add`

```
lin favorites add [flags]

Flags:
  --issue <identifier>    Favorite an issue
  --project <id>          Favorite a project
  --cycle <id>            Favorite a cycle
  --view <id>             Favorite a custom view
  --document <id>         Favorite a document
  --label <id>            Favorite a label

GraphQL: favoriteCreate(input: FavoriteCreateInput)
```

#### `lin favorites remove <id>`

```
lin favorites remove <id>

GraphQL: favoriteDelete(id)
```

---

### 5.13 Initiatives

#### `lin initiatives list`

```
lin initiatives list [flags]

Flags:
  --status <type>     Filter by status (Planned|Active|Completed)
  --all               Fetch all pages

GraphQL: initiatives(filter: InitiativeFilter)
Table columns: NAME | STATUS | HEALTH | OWNER | TARGET DATE
```

#### `lin initiatives show <id>`

```
lin initiatives show <id>

GraphQL: initiative(id)
Output: Detail view with projects, updates, health
```

---

### 5.14 Search

#### `lin search <query>`

```
lin search <query> [flags]

Flags:
  --type <type>      Filter by type: issues|projects|docs (default: all via semantic search)
  --team <key>       Scope to team
  --limit <n>        Max results per type (default: 10)

GraphQL:
  Default: semanticSearch(query, types, maxResults)
  --type issues: searchIssues(term)
  --type projects: searchProjects(term)
  --type docs: searchDocuments(term)

Output: Grouped results by type
```

**Example:**
```bash
lin search "authentication bug"
lin search "Q1 roadmap" --type projects
lin search "API design" --type docs
```

---

### 5.15 Webhooks

#### `lin webhooks list`

```
lin webhooks list

GraphQL: webhooks()
Table columns: ID | LABEL | URL | ENABLED
```

#### `lin webhooks show <id>`

```
lin webhooks show <id>

GraphQL: webhook(id)
```

#### `lin webhooks create`

```
lin webhooks create [flags]

Flags:
  --url <url>         Webhook URL (required)
  --label <text>      Label
  --team <key>        Scope to team
  --enabled           Enable immediately (default: true)

GraphQL: webhookCreate(input: WebhookCreateInput)
```

#### `lin webhooks update <id>`

```
lin webhooks update <id> [flags]

Flags:
  --url <url>         Update URL
  --label <text>      Update label
  --enabled <bool>    Enable/disable

GraphQL: webhookUpdate(input, id)
```

#### `lin webhooks delete <id>`

```
lin webhooks delete <id> [--yes]

GraphQL: webhookDelete(id)
```

---

### 5.16 Integrations

#### `lin integrations list`

```
lin integrations list

GraphQL: integrations()
Table columns: SERVICE | TEAM | CREATOR | DATE
```

#### `lin integrations show <id>`

```
lin integrations show <id>

GraphQL: integration(id)
```

---

### 5.17 Organization

#### `lin org`

```
lin org

GraphQL: organization()
Output: Organization detail (name, URL key, user count, plan, settings)
```

---

### 5.18 Config

#### `lin config init`

```
lin config init

Interactive setup:
1. Prompt for API key
2. Validate with viewer() query
3. Write ~/.config/lin/config.toml
4. Show current user info
```

#### `lin config set <key> <value>`

```
lin config set <key> <value>

Keys:
  api_key          API key
  defaults.team    Default team key
  defaults.output  Default output format (table|json|csv)
  display.color    Enable colors (true|false)
  display.page_size Default page size
```

#### `lin config get <key>`

```
lin config get <key>

Output: Current value for the key
```

#### `lin config list`

```
lin config list

Output: All current configuration key-value pairs
```

---

### 5.19 Utility Commands

#### `lin rate-limit`

```
lin rate-limit

GraphQL: rateLimitStatus()
Output: Current rate limit status (remaining requests, reset time)
```

#### `lin cache clear`

```
lin cache clear [--table <name>]

Clears the local SQLite cache. Optionally clear only a specific table.
```

---

### 5.20 TUI (Phase 5)

#### `lin tui`

```
lin tui [flags]

Flags:
  --team <key>     Start with team view

Features (FTXUI-based):
  - Kanban board view (columns = workflow states)
  - Issue detail panel (split view)
  - Vim keybindings (j/k navigation, Enter to open, q to quit)
  - Fuzzy search (/ to search)
  - Quick actions (a=assign, p=priority, s=state, l=label)
```

---

## 6. Build System

### 6.1 CMake Configuration

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(lin VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies via FetchContent
include(FetchContent)

# nlohmann/json - JSON parsing
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

# CLI11 - Argument parsing
FetchContent_Declare(cli11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.4.2
)

# toml++ - TOML config parsing
FetchContent_Declare(tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)

# FTXUI - TUI framework (Phase 5)
# FetchContent_Declare(ftxui
#     GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui.git
#     GIT_TAG v5.0.0
# )

FetchContent_MakeAvailable(json cli11 tomlplusplus)

# System dependencies
find_package(CURL REQUIRED)
# find_package(SQLite3 REQUIRED)  # Phase 6

# Main executable
add_executable(lin
    src/main.cpp
    src/core/http_client.cpp
    src/core/graphql.cpp
    src/core/auth.cpp
    src/core/config.cpp
    src/core/output.cpp
    src/core/color.cpp
    src/core/paginator.cpp
    src/core/filter.cpp
    src/core/error.cpp
    # Modules added as implemented
    src/modules/issues/api.cpp
    src/modules/issues/commands.cpp
    # ...
)

target_include_directories(lin PRIVATE src)

target_link_libraries(lin PRIVATE
    nlohmann_json::nlohmann_json
    CLI11::CLI11
    tomlplusplus::tomlplusplus
    CURL::libcurl
    # SQLite::SQLite3  # Phase 6
    # ftxui::screen ftxui::dom ftxui::component  # Phase 5
)

# Install
install(TARGETS lin DESTINATION bin)

# Tests
enable_testing()
add_subdirectory(tests)
```

### 6.2 Makefile Wrapper

```makefile
# Makefile
.PHONY: build install test clean debug release

BUILD_DIR = build

build:
	cmake -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Release
	cmake --build $(BUILD_DIR) -j$(shell nproc 2>/dev/null || sysctl -n hw.ncpu)

debug:
	cmake -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug
	cmake --build $(BUILD_DIR) -j$(shell nproc 2>/dev/null || sysctl -n hw.ncpu)

install: build
	cmake --install $(BUILD_DIR) --prefix /usr/local

test:
	cmake -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug
	cmake --build $(BUILD_DIR) --target lin_tests
	cd $(BUILD_DIR) && ctest --output-on-failure

clean:
	rm -rf $(BUILD_DIR)

format:
	find src tests -name '*.cpp' -o -name '*.h' | xargs clang-format -i

lint:
	cmake -B $(BUILD_DIR) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	clang-tidy src/**/*.cpp -p $(BUILD_DIR)
```

### 6.3 Build Targets

| Target | Platform | Compiler | Notes |
|--------|----------|----------|-------|
| Primary | macOS arm64 | Apple clang++ (C++20) | Development target |
| Secondary | Linux x86_64 | g++/clang++ (C++20) | CI/release target |

**Static binary goal:** Link libcurl and SQLite3 statically where possible. On macOS, use system libcurl (dynamic). On Linux, static linking via `-DCURL_STATICLIB`.

### 6.4 Dependencies Summary

| Dependency | Version | Purpose | Fetch Method |
|------------|---------|---------|--------------|
| libcurl | System | HTTP client | `find_package` |
| nlohmann/json | 3.11.3 | JSON parsing | FetchContent |
| CLI11 | 2.4.2 | Argument parsing | FetchContent |
| toml++ | 3.4.0 | TOML config files | FetchContent |
| SQLite3 | System | Local cache (Phase 6) | `find_package` |
| FTXUI | 5.0.0 | Terminal UI (Phase 5) | FetchContent |
| Google Test | Latest | Unit testing | FetchContent |

---

## 7. Implementation Order

### Phase 1: Core Infrastructure + Issues Module

**Goal:** Prove the full pattern end-to-end with the most complex module.

1. **Project scaffolding** — CMakeLists.txt, Makefile, directory structure, `.clang-format`
2. **Core: HTTP client** — libcurl wrapper, POST to Linear GraphQL endpoint
3. **Core: JSON parsing** — nlohmann/json setup, `from_json` pattern for PageInfo/Connection
4. **Core: Auth** — `LINEAR_API_KEY` env var loading, config file fallback
5. **Core: Error handling** — GraphQL error parsing, HTTP error codes, rate limit retry
6. **Core: Config** — toml++ config loading/saving, `lin config init/set/get/list`
7. **Core: Output formatting** — Table renderer, detail view, JSON output, color, pipe detection
8. **Core: Pagination** — Cursor-based paginator template
9. **Core: Filter builder** — IssueFilter construction from CLI flags
10. **Issues module** — Full CRUD: `list`, `show`, `create`, `update`, `delete`, `archive`, `search`, `assign`, `label`, `move`, `relate`, `attach`, `subscribe`, `branch`, `bulk update`
11. **`lin me` command** — Uses `viewer()` query

### Phase 2: Supporting Data Modules

**Goal:** Modules needed to resolve references in Issues (team names, user names, labels, states).

12. **Teams module** — `list`, `show`, `members`, `states`, `labels`, `cycles`
13. **Labels module** — `list`, `show`, `create`, `update`, `delete`
14. **Workflow States** — Listed via Teams module (`lin teams states`)
15. **Users module** — `list`, `show`
16. **Filter resolution** — Resolve team keys, user names, label names, state names to IDs

### Phase 3: Project Ecosystem

**Goal:** Projects and related entities.

17. **Projects module** — `list`, `show`, `create`, `update`, `delete`, `search`, `milestones` (CRUD), `updates` (list, create), `members`
18. **Cycles module** — `list`, `show`, `current`, `create`, `update`, `archive`, `issues`
19. **Comments module** — `list`, `show`, `create`, `update`, `delete`

### Phase 4: Everything Else

**Goal:** Remaining modules for full feature coverage.

20. **Documents module** — `list`, `show`, `create`, `update`, `delete`, `search`
21. **Custom Views module** — `list`, `show`, `create`, `delete`
22. **Notifications module** — `list`, `show`, `count`, `read`, `archive`, `snooze`
23. **Favorites module** — `list`, `add`, `remove`
24. **Initiatives module** — `list`, `show`
25. **Search module** — `lin search` (semantic + typed search)
26. **Webhooks module** — `list`, `show`, `create`, `update`, `delete`
27. **Integrations module** — `list`, `show` (read-only)
28. **Organization module** — `lin org`
29. **Rate limit command** — `lin rate-limit`

### Phase 5: TUI Mode

**Goal:** Interactive terminal UI.

30. **FTXUI integration** — Add dependency, basic app shell
31. **Kanban board** — Columns per workflow state, issue cards
32. **Issue detail panel** — Split view with full issue info
33. **Navigation** — Vim keybindings (j/k/h/l, Enter, Esc, q)
34. **Quick actions** — Keyboard shortcuts for assign, state change, priority
35. **Fuzzy search** — `/` to search issues

### Phase 6: Local Cache

**Goal:** Speed up filter resolution and enable offline viewing.

36. **SQLite setup** — Create/migrate database schema
37. **Cache layer** — Store teams, users, labels, states
38. **Cache invalidation** — TTL-based, manual `lin cache clear`
39. **Offline issue viewing** — Cache recently viewed issues
40. **Background sync** — Refresh cache on startup if stale

---

## 8. Testing Strategy

### 8.1 Unit Tests

**Framework:** Google Test (via FetchContent)

**Coverage targets:**

| Component | Tests | Priority |
|-----------|-------|----------|
| JSON parsing (`from_json`) | Parse valid JSON, handle missing fields, handle null fields, handle malformed JSON | P0 |
| Table renderer | Column alignment, truncation, UTF-8 width, no-color mode | P0 |
| Filter builder | IssueFilter construction, empty filters, combined filters | P0 |
| Config parser | Valid TOML, missing fields, default values | P1 |
| Pagination | Single page, multi-page, empty results | P1 |
| Color utilities | ANSI codes, disabled mode, hex color conversion | P2 |
| Error parsing | GraphQL errors, rate limit errors, network errors | P1 |

**Example test:**

```cpp
// tests/test_issue_parsing.cpp

TEST(IssueModel, ParsesMinimalIssue) {
    auto j = json::parse(R"({
        "id": "abc-123",
        "title": "Fix bug",
        "identifier": "ENG-1",
        "number": 1,
        "priority": 2,
        "priorityLabel": "High",
        "url": "https://linear.app/...",
        "branchName": "eng-1-fix-bug"
    })");

    Issue issue;
    from_json(j, issue);

    EXPECT_EQ(issue.id, "abc-123");
    EXPECT_EQ(issue.title, "Fix bug");
    EXPECT_EQ(issue.identifier, "ENG-1");
    EXPECT_EQ(issue.priority, 2.0);
    EXPECT_EQ(issue.assignee_name, std::nullopt);
}

TEST(IssueModel, ParsesFullIssue) {
    auto j = json::parse(R"({
        "id": "abc-123",
        "title": "Fix bug",
        "identifier": "ENG-1",
        "number": 1,
        "priority": 2,
        "priorityLabel": "High",
        "url": "https://linear.app/...",
        "branchName": "eng-1-fix-bug",
        "description": "Detailed description",
        "dueDate": "2026-03-15",
        "assignee": { "id": "user-1", "displayName": "Jane" },
        "state": { "id": "state-1", "name": "In Progress", "type": "started" },
        "team": { "id": "team-1", "name": "Engineering", "key": "ENG" },
        "labels": { "nodes": [{"id": "l1", "name": "Bug", "color": "#FF0000"}] }
    })");

    Issue issue;
    from_json(j, issue);

    EXPECT_EQ(issue.assignee_name, "Jane");
    EXPECT_EQ(issue.state_name, "In Progress");
    EXPECT_EQ(issue.state_type, "started");
    EXPECT_EQ(issue.team_key, "ENG");
    EXPECT_EQ(issue.label_names.size(), 1);
}

TEST(IssueModel, HandlesNullFields) {
    auto j = json::parse(R"({
        "id": "abc-123",
        "title": "Fix bug",
        "identifier": "ENG-1",
        "number": 1,
        "priority": 0,
        "priorityLabel": "No priority",
        "url": "https://linear.app/...",
        "branchName": "eng-1-fix-bug",
        "assignee": null,
        "state": null,
        "team": null,
        "description": null,
        "dueDate": null
    })");

    Issue issue;
    from_json(j, issue);

    EXPECT_EQ(issue.assignee_name, std::nullopt);
    EXPECT_EQ(issue.state_name, std::nullopt);
    EXPECT_EQ(issue.description, std::nullopt);
}
```

### 8.2 Integration Tests

**Requirement:** `LINEAR_API_KEY` environment variable set to a valid key.

**Guarded:** Tests skip if `LINEAR_API_KEY` is not set.

```cpp
// tests/integration/test_issues_api.cpp

class IssuesApiTest : public ::testing::Test {
protected:
    void SetUp() override {
        auto key = std::getenv("LINEAR_API_KEY");
        if (!key) {
            GTEST_SKIP() << "LINEAR_API_KEY not set, skipping integration test";
        }
    }
};

TEST_F(IssuesApiTest, ListIssuesReturnsResults) {
    auto connection = list_issues({.first = 5});
    EXPECT_FALSE(connection.nodes.empty());
    EXPECT_FALSE(connection.nodes[0].id.empty());
    EXPECT_FALSE(connection.nodes[0].identifier.empty());
}

TEST_F(IssuesApiTest, ViewerReturnsCurrentUser) {
    auto user = get_viewer();
    EXPECT_FALSE(user.id.empty());
    EXPECT_FALSE(user.email.empty());
    EXPECT_TRUE(user.is_me);
}
```

### 8.3 Mock HTTP Layer

For offline testing, provide a mock HTTP client that returns pre-recorded responses.

```cpp
// tests/mocks/mock_http_client.h

class MockHttpClient : public HttpClientBase {
public:
    void add_response(const std::string& query_contains, const std::string& response_body);

    HttpResponse post(
        const std::string& url,
        const std::string& body,
        const std::vector<std::pair<std::string, std::string>>& headers
    ) override;

private:
    std::vector<std::pair<std::string, std::string>> responses_;
};
```

This allows testing the full command pipeline (CLI args → API call → JSON parse → output render) without network access.

### 8.4 Test CMake Configuration

```cmake
# tests/CMakeLists.txt
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

add_executable(lin_tests
    test_issue_parsing.cpp
    test_project_parsing.cpp
    test_table_renderer.cpp
    test_filter_builder.cpp
    test_config_parser.cpp
    test_pagination.cpp
    test_color.cpp
    test_error_parsing.cpp
    # Integration tests
    integration/test_issues_api.cpp
    integration/test_viewer.cpp
)

target_link_libraries(lin_tests PRIVATE
    GTest::gtest_main
    nlohmann_json::nlohmann_json
    tomlplusplus::tomlplusplus
    CURL::libcurl
)

target_include_directories(lin_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(lin_tests)
```

### 8.5 CI Pipeline (Future)

```yaml
# .github/workflows/ci.yml
name: CI
on: [push, pull_request]

jobs:
  build-test:
    strategy:
      matrix:
        os: [macos-14, ubuntu-24.04]
    runs-on: ${{ matrix.os }}
    steps:
      - uses: actions/checkout@v4
      - name: Install dependencies
        run: |
          if [ "$RUNNER_OS" == "Linux" ]; then
            sudo apt-get install -y libcurl4-openssl-dev libsqlite3-dev
          fi
      - name: Build
        run: make build
      - name: Test (unit)
        run: make test
      - name: Test (integration)
        if: env.LINEAR_API_KEY != ''
        env:
          LINEAR_API_KEY: ${{ secrets.LINEAR_API_KEY }}
        run: make test
```
