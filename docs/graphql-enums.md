# Linear GraphQL API — Enums

## AgentActivitySignal
A modifier that provides additional instructions on how the activity should be interpreted.

- `stop`
- `continue`
- `auth`
- `select`

## AgentActivityType
The type of an agent activity.

- `thought`
- `action`
- `response`
- `elicitation`
- `error`
- `prompt`

## AgentSessionStatus
The status of an agent session.

- `pending`
- `active`
- `complete`
- `awaitingInput`
- `error`
- `stale`

## AgentSessionType
[DEPRECATED] The type of an agent session.

- `commentThread`

## AuthenticationSessionType
- `web`
- `desktop`
- `ios`
- `android`

## ContextViewType
- `activeIssues`
- `activeCycle`
- `upcomingCycle`
- `backlog`
- `triage`

## CustomerStatusType
[DEPRECATED] A type of customer status.

- `active`
- `inactive`

## CustomerVisibilityMode
Mode that controls who can see and set Customers in Slack Asks.

- `LinearOnly`
- `SlackMembers`
- `SlackMembersAndGuests`

## CyclePeriod
- `before`
- `during`
- `after`

## DateResolutionType
By which resolution is a date defined.

- `month`
- `quarter`
- `halfYear`
- `year`

## Day
The day of the week.

- `Sunday`
- `Monday`
- `Tuesday`
- `Wednesday`
- `Thursday`
- `Friday`
- `Saturday`

## EmailIntakeAddressType
The type of the email address.

- `team`
- `template`
- `asks`
- `asksWeb`

## ExternalSyncService
The service that syncs an external entity to Linear.

- `jira`
- `github`
- `slack`

## FacetPageSource
- `projects`
- `teamIssues`
- `feed`

## FeedSummarySchedule
Cadence to generate feed summary

- `daily`
- `weekly`
- `never`

## FrequencyResolutionType
By which resolution is frequency defined.

- `daily`
- `weekly`

## GitAutomationStates
The various states of a pull/merge request.

- `draft`
- `start`
- `review`
- `mergeable`
- `merge`

## GitLinkKind
[Internal] The kind of link between an issue and a pull request.

- `closes`
- `contributes`
- `links`

## GithubOrgType
- `user`
- `organization`

## IdentityProviderType
The type of identity provider.

- `general`
- `webForms`

## InitiativeStatus
- `Planned`
- `Active`
- `Completed`

## InitiativeTab
Different tabs available inside an initiative.

- `overview`
- `projects`
- `updates`

## InitiativeUpdateHealthType
The health type when the update is created.

- `onTrack`
- `atRisk`
- `offTrack`

## IntegrationService
Linear supported integration services.

- `airbyte`
- `discord`
- `figma`
- `figmaPlugin`
- `front`
- `github`
- `gong`
- `githubEnterpriseServer`
- `githubCommit`
- `githubImport`
- `githubPersonal`
- `githubCodeAccessPersonal`
- `gitlab`
- `googleCalendarPersonal`
- `googleSheets`
- `intercom`
- `jira`
- `jiraPersonal`
- `launchDarkly`
- `launchDarklyPersonal`
- `loom`
- `notion`
- `opsgenie`
- `pagerDuty`
- `salesforce`
- `slack`
- `slackAsks`
- `slackCustomViewNotifications`
- `slackOrgProjectUpdatesPost`
- `slackOrgInitiativeUpdatesPost`
- `slackPersonal`
- `slackPost`
- `slackProjectPost`
- `slackProjectUpdatesPost`
- `slackInitiativePost`
- `sentry`
- `zendesk`
- `email`
- `mcpServerPersonal`
- `mcpServer`
- `microsoftTeams`
- `microsoftPersonal`

## IssueRelationType
The type of the issue relation.

- `blocks`
- `duplicate`
- `related`
- `similar`

## IssueSuggestionState
- `active`
- `stale`
- `accepted`
- `dismissed`

## IssueSuggestionType
- `team`
- `project`
- `assignee`
- `label`
- `similarIssue`
- `relatedIssue`

## NotificationCategory
The categories of notifications a user can subscribe to.

- `assignments`
- `statusChanges`
- `commentsAndReplies`
- `mentions`
- `reactions`
- `subscriptions`
- `documentChanges`
- `postsAndUpdates`
- `reminders`
- `reviews`
- `appsAndIntegrations`
- `triage`
- `customers`
- `feed`
- `system`

## NotificationChannel
The delivery channels a user can receive notifications in.

- `desktop`
- `mobile`
- `email`
- `slack`

## OAuthClientApprovalStatus
The different requests statuses possible for an OAuth client approval request.

- `requested`
- `approved`
- `denied`

## OrganizationDomainAuthType
What type of auth is the domain used for.

- `saml`
- `general`

## OrganizationInviteStatus
The different statuses possible for an organization invite.

- `pending`
- `accepted`
- `expired`

## PaginationNulls
How to treat NULL values, whether they should appear first or last

- `first`
- `last`

## PaginationOrderBy
By which field should the pagination order by

- `createdAt`
- `updatedAt`

## PaginationSortOrder
Whether to sort in ascending or descending order

- `Ascending`
- `Descending`

## PostType
Type of Post

- `summary`
- `update`

## ProductIntelligenceScope
[Internal] The scope of product intelligence suggestion data for a team.

- `workspace`
- `teamHierarchy`
- `team`
- `none`

## ProjectMilestoneStatus
The status of a project milestone.

- `unstarted`
- `next`
- `overdue`
- `done`

## ProjectStatusType
A type of project status.

- `backlog`
- `planned`
- `started`
- `paused`
- `completed`
- `canceled`

## ProjectTab
Different tabs available inside a project.

- `customers`
- `documents`
- `issues`
- `updates`

## ProjectUpdateHealthType
The health type when the project update is created.

- `onTrack`
- `atRisk`
- `offTrack`

## ProjectUpdateReminderFrequency
The frequency at which to send project update reminders.

- `week`
- `twoWeeks`
- `month`
- `never`

## PullRequestMergeMethod
The method used to merge a pull request.

- `MERGE`
- `REBASE`
- `SQUASH`

## PullRequestReviewTool
- `source`
- `graphite`

## PullRequestStatus
The status of a pull request.

- `draft`
- `open`
- `inReview`
- `approved`
- `merged`
- `closed`

## PushSubscriptionType
The different push subscription types.

- `web`
- `apple`
- `appleDevelopment`
- `firebase`

## ReleaseChannel
Features release channel.

- `development`
- `internal`
- `privateBeta`
- `beta`
- `preRelease`
- `public`

## ReleasePipelineType
A type of release pipeline.

- `continuous`
- `scheduled`

## ReleaseStageType
A type of release stage.

- `planned`
- `started`
- `completed`
- `canceled`

## SLADayCountType
- `all`
- `onlyBusinessDays`

## SemanticSearchResultType
The type of the semantic search result.

- `issue`
- `project`
- `initiative`
- `document`

## SendStrategy
- `desktopThenPush`
- `desktopAndPush`
- `desktop`
- `push`

## SlaStatus
- `Breached`
- `HighRisk`
- `MediumRisk`
- `LowRisk`
- `Completed`
- `Failed`

## SlackChannelType
- `DirectMessage`
- `MultiPersonDirectMessage`
- `Private`
- `PrivateGroup`
- `Public`

## SummaryGenerationStatus
The generation status of a summary.

- `pending`
- `completed`
- `failed`

## TeamRetirementSubTeamHandling
[Internal] How to handle sub-teams when retiring a parent team.

- `unnest`
- `retire`

## TeamRoleType
All possible roles within a team in terms of access to team settings and operations.

- `owner`
- `member`

## TriageResponsibilityAction
Which action should be taken after an issue is added to triage.

- `assign`
- `notify`

## TriageRuleErrorType
The type of error that occurred during triage rule execution.

- `cycle`
- `default`
- `labelGroupConflict`

## UserContextViewType
- `assigned`

## UserFlagType
The types of flags that the user can have.

- `updatedSlackThreadSyncIntegration`
- `completedOnboarding`
- `desktopInstalled`
- `teamsPageIntroductionDismissed`
- `joinTeamIntroductionDismissed`
- `desktopDownloadToastDismissed`
- `emptyBacklogDismissed`
- `emptyCustomViewsDismissed`
- `emptyActiveIssuesDismissed`
- `emptyMyIssuesDismissed`
- `triageWelcomeDismissed`
- `cycleWelcomeDismissed`
- `projectWelcomeDismissed`
- `projectBacklogWelcomeDismissed`
- `projectUpdatesWelcomeDismissed`
- `pulseWelcomeDismissed`
- `analyticsWelcomeDismissed`
- `insightsWelcomeDismissed`
- `insightsHelpDismissed`
- `figmaPromptDismissed`
- `issueMovePromptCompleted`
- `migrateThemePreference`
- `listSelectionTip`
- `emptyParagraphSlashCommandTip`
- `editorSlashCommandUsed`
- `canPlaySnake`
- `canPlayTetris`
- `importBannerDismissed`
- `tryInvitePeopleDismissed`
- `tryRoadmapsDismissed`
- `tryCyclesDismissed`
- `tryTriageDismissed`
- `tryGithubDismissed`
- `rewindBannerDismissed`
- `helpIslandFeatureInsightsDismissed`
- `dueDateShortcutMigration`
- `slackCommentReactionTipShown`
- `issueLabelSuggestionUsed`
- `threadedCommentsNudgeIsSeen`
- `desktopTabsOnboardingDismissed`
- `milestoneOnboardingIsSeenAndDismissed`
- `projectBoardOnboardingIsSeenAndDismissed`
- `figmaPluginBannerDismissed`
- `initiativesBannerDismissed`
- `commandMenuClearShortcutTip`
- `slackBotWelcomeMessageShown`
- `slackAgentPromoFromCreateNewIssueShown`
- `all`

## UserFlagUpdateOperation
Operations that can be applied to UserFlagType.

- `incr`
- `decr`
- `clear`
- `lock`

## UserRoleType
The different permission roles available to users on an organization.

- `owner`
- `admin`
- `guest`
- `user`
- `app`

## UserSettingsThemeDeviceType
Device type for theme

- `desktop`
- `mobileWeb`

## UserSettingsThemeMode
Theme color mode

- `light`
- `dark`

## UserSettingsThemePreset
Theme preset options

- `system`
- `light`
- `pureLight`
- `dark`
- `magicBlue`
- `classicDark`
- `custom`

## ViewPreferencesType
The type of view preferences (either user or organization level preferences).

- `organization`
- `user`

## ViewType
The client view this custom view is targeting.

- `inbox`
- `myIssues`
- `myIssuesCreatedByMe`
- `myIssuesSubscribedTo`
- `myIssuesActivity`
- `myIssuesSharedWithMe`
- `userProfile`
- `userProfileCreatedByUser`
- `board`
- `completedCycle`
- `cycle`
- `release`
- `continuousPipelineReleases`
- `project`
- `projectDocuments`
- `label`
- `triage`
- `activeIssues`
- `backlog`
- `subIssues`
- `allIssues`
- `dashboards`
- `customView`
- `customViews`
- `initiative`
- `initiativeOverview`
- `initiativeOverviewSubInitiatives`
- `initiatives`
- `initiativesPlanned`
- `initiativesCompleted`
- `projects`
- `projectsAll`
- `projectsBacklog`
- `projectsClosed`
- `projectLabel`
- `search`
- `splitSearch`
- `teams`
- `archive`
- `quickView`
- `issueIdentifiers`
- `customers`
- `customer`
- `embeddedCustomerNeeds`
- `projectCustomerNeeds`
- `reviews`
- `myReviews`
- `createdReviews`
- `agents`
- `feedAll`
- `feedCreated`
- `feedFollowing`
- `feedPopular`
- `workspaceMembers`
- `releasePipelines`
- `roadmapAll`
- `roadmap`
- `roadmaps`
- `roadmapClosed`
- `roadmapBacklog`

## WorkflowTrigger
- `entityCreated`
- `entityUpdated`
- `entityCreatedOrUpdated`
- `entityRemoved`
- `entityUnarchived`

## WorkflowTriggerType
- `issue`
- `project`

## WorkflowType
- `sla`
- `custom`
- `viewSubscription`
- `triage`
