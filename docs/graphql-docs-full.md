# Linear GraphQL API — Full Schema Reference

## Overview
- 422 object types
- 71 enums
- 337 input types

## Queries

### workflowStates(filter: WorkflowStateFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → WorkflowStateConnection
All issue workflow states.

### workflowState(id: NON_NULL) → WorkflowState
One specific state.

### webhooks(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → WebhookConnection
All webhooks.

### webhook(id: NON_NULL) → Webhook
A specific webhook.

### failuresForOauthWebhooks(oauthClientId: NON_NULL) → NON_NULL
[INTERNAL] Webhook failure events for webhooks that belong to an OAuth application. (last 50)

### userSettings() → UserSettings
The user's settings.

### users(filter: UserFilter, includeDisabled: Boolean, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy, sort: LIST) → UserConnection
All users for the organization.

### user(id: NON_NULL) → User
One specific user.

### viewer() → User
The currently authenticated user.

### userSessions(id: NON_NULL) → NON_NULL
Lists the sessions of a user. Can only be called by an admin or owner.

### triageResponsibilities(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → TriageResponsibilityConnection
All triage responsibilities.

### triageResponsibility(id: NON_NULL) → TriageResponsibility
A specific triage responsibility.

### timeSchedules(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → TimeScheduleConnection
All time schedules.

### timeSchedule(id: NON_NULL) → TimeSchedule
A specific time schedule.

### templates() → NON_NULL
All templates from all users.

### template(id: NON_NULL) → Template
A specific template.

### templatesForIntegration(integrationType: NON_NULL) → NON_NULL
Returns all templates that are associated with the integration type.

### projects(filter: ProjectFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy, sort: LIST) → ProjectConnection
All projects.

### project(id: NON_NULL) → Project
One specific project.

### projectFilterSuggestion(prompt: NON_NULL) → ProjectFilterSuggestionPayload
Suggests filters for a project view based on a text prompt.

### teams(filter: TeamFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → TeamConnection
All teams whose issues can be accessed by the user. This might be different from `administrableTeams`, which also includes teams whose settings can be changed by the user.

### administrableTeams(filter: TeamFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → TeamConnection
All teams you the user can administrate. Administrable teams are teams whose settings the user can change, but to whose issues the user doesn't necessarily have access to.

### team(id: NON_NULL) → Team
One specific team.

### teamMemberships(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → TeamMembershipConnection
All team memberships.

### teamMembership(id: NON_NULL) → TeamMembership
One specific team membership.

### semanticSearch(query: NON_NULL, types: LIST, maxResults: Int, includeArchived: Boolean, filters: SemanticSearchFilters) → SemanticSearchPayload
Search for various resources using natural language.

### searchDocuments(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy, term: NON_NULL, includeComments: Boolean, teamId: String) → DocumentSearchPayload
Search documents.

### searchProjects(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy, term: NON_NULL, includeComments: Boolean, teamId: String) → ProjectSearchPayload
Search projects.

### searchIssues(filter: IssueFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy, term: NON_NULL, includeComments: Boolean, teamId: String) → IssueSearchPayload
Search issues.

### releaseStages(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → ReleaseStageConnection
[ALPHA] All release stages.

### releaseStage(id: NON_NULL) → ReleaseStage
[ALPHA] One specific release stage.

### releases(filter: ReleaseFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → ReleaseConnection
[ALPHA] All releases.

### release(id: NON_NULL) → Release
[ALPHA] One specific release.

### releasePipelines(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → ReleasePipelineConnection
[ALPHA] All release pipelines.

### releasePipeline(id: NON_NULL) → ReleasePipeline
[ALPHA] One specific release pipeline.

### releasePipelineByAccessKey() → ReleasePipeline
[ALPHA] Returns a release pipeline by ID. Requires the access key to have access to the pipeline.

### latestReleaseByAccessKey() → Release
[ALPHA] Returns the latest release for the pipeline associated with the access key.

### rateLimitStatus() → RateLimitPayload
The status of the rate limiter.

### pushSubscriptionTest(targetMobile: Boolean, sendStrategy: SendStrategy) → PushSubscriptionTestPayload
Sends a test push message.

### projectUpdates(filter: ProjectUpdateFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → ProjectUpdateConnection
All project updates.

### projectUpdate(id: NON_NULL) → ProjectUpdate
A specific project update.

### projectStatuses(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → ProjectStatusConnection
All project statuses.

### projectStatusProjectCount(id: NON_NULL) → ProjectStatusCountPayload
[INTERNAL] Count of projects using this project status across the organization.

### projectStatus(id: NON_NULL) → ProjectStatus
One specific project status.

### projectRelations(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → ProjectRelationConnection
All project relationships.

### projectRelation(id: NON_NULL) → ProjectRelation
One specific project relation.

### projectMilestones(filter: ProjectMilestoneFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → ProjectMilestoneConnection
All milestones for the project.

### projectMilestone(id: NON_NULL) → ProjectMilestone
One specific project milestone.

### projectLabels(filter: ProjectLabelFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → ProjectLabelConnection
All project labels.

### projectLabel(id: NON_NULL) → ProjectLabel
One specific label.

### organization() → Organization
The user's organization.

### organizationExists(urlKey: NON_NULL) → OrganizationExistsPayload
Does the organization exist.

### archivedTeams() → NON_NULL
[Internal] All archived teams of the organization.

### organizationMeta(urlKey: NON_NULL) → OrganizationMeta
[INTERNAL] Get organization metadata by urlKey or organization id.

### organizationInvites(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → OrganizationInviteConnection
All invites for the organization.

### organizationInvite(id: NON_NULL) → OrganizationInvite
One specific organization invite.

### organizationInviteDetails(id: NON_NULL) → OrganizationInviteDetailsPayload
One specific organization invite.

### organizationDomainClaimRequest(id: NON_NULL) → OrganizationDomainClaimPayload
[INTERNAL] Checks whether the domain can be claimed.

### notificationSubscriptions(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → NotificationSubscriptionConnection
The user's notification subscriptions.

### notificationSubscription(id: NON_NULL) → NotificationSubscription
One specific notification subscription.

### notifications(filter: NotificationFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → NotificationConnection
All notifications.

### notificationsUnreadCount() → Int
[Internal] A number of unread notifications.

### notification(id: NON_NULL) → Notification
One specific notification.

### issueToReleases(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → IssueToReleaseConnection
[ALPHA] Returns a list of issue to release entities.

### issueToRelease(id: NON_NULL) → IssueToRelease
[ALPHA] One specific issueToRelease.

### issues(filter: IssueFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy, sort: LIST) → IssueConnection
All issues.

### issue(id: NON_NULL) → Issue
One specific issue.

### issueSearch(filter: IssueFilter, query: String, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → IssueConnection
[DEPRECATED] Search issues. This endpoint is deprecated and will be removed in the future – use `searchIssues` instead.

### issueVcsBranchSearch(branchName: NON_NULL) → Issue
Find issue based on the VCS branch name.

### issueFigmaFileKeySearch(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy, fileKey: NON_NULL) → IssueConnection
Find issues that are related to a given Figma file key.

### issuePriorityValues() → NON_NULL
Issue priority values and corresponding labels.

### issueFilterSuggestion(projectId: String, prompt: NON_NULL) → IssueFilterSuggestionPayload
Suggests filters for an issue view based on a text prompt.

### issueRepositorySuggestions(agentSessionId: String, candidateRepositories: NON_NULL, issueId: NON_NULL) → RepositorySuggestionsPayload
Returns code repositories that are most likely to be relevant for implementing an issue.

### issueRelations(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → IssueRelationConnection
All issue relationships.

### issueRelation(id: NON_NULL) → IssueRelation
One specific issue relation.

### issueLabels(filter: IssueLabelFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → IssueLabelConnection
All issue labels.

### issueLabel(id: NON_NULL) → IssueLabel
One specific label.

### issueImportCheckCSV(csvUrl: NON_NULL, service: NON_NULL) → IssueImportCheckPayload
Checks a CSV file validity against a specific import service.

### issueImportCheckSync(issueImportId: NON_NULL) → IssueImportSyncCheckPayload
Checks whether it will be possible to setup sync for this project or repository at the end of import

### issueImportJqlCheck(jiraHostname: NON_NULL, jiraToken: NON_NULL, jiraEmail: NON_NULL, jiraProject: NON_NULL, jql: NON_NULL) → IssueImportJqlCheckPayload
Checks whether a custom JQL query is valid and can be used to filter issues of a Jira import

### integrationsSettings(id: NON_NULL) → IntegrationsSettings
One specific set of settings.

### integrationTemplates(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → IntegrationTemplateConnection
Template and integration connections.

### integrationTemplate(id: NON_NULL) → IntegrationTemplate
One specific integrationTemplate.

### integrations(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → IntegrationConnection
All integrations.

### integration(id: NON_NULL) → Integration
One specific integration.

### verifyGitHubEnterpriseServerInstallation(integrationId: NON_NULL) → GitHubEnterpriseServerInstallVerificationPayload
Verify that we received the correct response from the GitHub Enterprise Server.

### integrationHasScopes(scopes: NON_NULL, integrationId: NON_NULL) → IntegrationHasScopesPayload
Checks if the integration has all required scopes.

### initiativeUpdates(filter: InitiativeUpdateFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → InitiativeUpdateConnection
All  InitiativeUpdates.

### initiativeUpdate(id: NON_NULL) → InitiativeUpdate
A specific  initiative update.

### initiativeToProjects(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → InitiativeToProjectConnection
returns a list of initiative to project entities.

### initiativeToProject(id: NON_NULL) → InitiativeToProject
One specific initiativeToProject.

### initiatives(filter: InitiativeFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy, sort: LIST) → InitiativeConnection
All initiatives in the workspace.

### initiative(id: NON_NULL) → Initiative
One specific initiative.

### initiativeRelations(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → InitiativeRelationConnection
All initiative relationships.

### initiativeRelation(id: NON_NULL) → ProjectRelation
One specific initiative relation.

### fetchData(query: NON_NULL) → FetchDataPayload
[Internal] Fetch an arbitrary set of data using natural language query. Be specific about what you want including properties for each entity, sort order, filters, limit and properties.

### favorites(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → FavoriteConnection
The user's favorites.

### favorite(id: NON_NULL) → Favorite
One specific favorite.

### externalUsers(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → ExternalUserConnection
All external users for the organization.

### externalUser(id: NON_NULL) → ExternalUser
One specific external user.

### entityExternalLink(id: NON_NULL) → EntityExternalLink
One specific entity link.

### emojis(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → EmojiConnection
All custom emojis.

### emoji(id: NON_NULL) → Emoji
A specific emoji.

### emailIntakeAddress(id: NON_NULL) → EmailIntakeAddress
One specific email intake address.

### documents(filter: DocumentFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → DocumentConnection
All documents in the workspace.

### document(id: NON_NULL) → Document
One specific document.

### documentContentHistory(id: NON_NULL) → DocumentContentHistoryPayload
A collection of document content history entries.

### cycles(filter: CycleFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → CycleConnection
All cycles.

### cycle(id: NON_NULL) → Cycle
One specific cycle.

### customerTiers(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → CustomerTierConnection
All customer tiers.

### customerTier(id: NON_NULL) → CustomerTier
One specific customer tier.

### customerStatuses(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → CustomerStatusConnection
All customer statuses.

### customerStatus(id: NON_NULL) → CustomerStatus
One specific customer status.

### customers(filter: CustomerFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy, sorts: LIST) → CustomerConnection
All customers.

### customer(id: NON_NULL) → Customer
One specific customer.

### customerNeeds(filter: CustomerNeedFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → CustomerNeedConnection
All customer needs.

### customerNeed(id: String, hash: String) → CustomerNeed
One specific customer need

### issueTitleSuggestionFromCustomerRequest(request: NON_NULL) → IssueTitleSuggestionFromCustomerRequestPayload
Suggests issue title based on a customer request.

### customViews(filter: CustomViewFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy, sort: LIST) → CustomViewConnection
Custom views for the user.

### customView(id: NON_NULL) → CustomView
One specific custom view.

### customViewDetailsSuggestion(modelName: String, filter: NON_NULL) → CustomViewSuggestionPayload
[INTERNAL] Suggests metadata for a view based on it's filters.

### customViewHasSubscribers(id: NON_NULL) → CustomViewHasSubscribersPayload
Whether a custom view has other subscribers than the current user in the organization.

### comments(filter: CommentFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → CommentConnection
All comments.

### comment(id: String, hash: String) → Comment
A specific comment.

### availableUsers() → AuthResolverResponse
Fetch users belonging to this user account.

### authenticationSessions() → NON_NULL
User's active sessions.

### ssoUrlFromEmail(isDesktop: Boolean, type: NON_NULL, email: NON_NULL) → SsoUrlFromEmailResponse
Fetch SSO login URL for the email provided.

### auditEntryTypes() → NON_NULL
List of audit entry types.

### auditEntries(filter: AuditEntryFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → AuditEntryConnection
All audit log entries.

### attachments(filter: AttachmentFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → AttachmentConnection
All issue attachments.

To get attachments for a given URL, use `attachmentsForURL` query.

### attachment(id: NON_NULL) → Attachment

One specific issue attachment.
[Deprecated] 'url' can no longer be used as the 'id' parameter. Use 'attachmentsForUrl' instead

### attachmentsForURL(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy, url: NON_NULL) → AttachmentConnection
Returns issue attachments for a given `url`.

### attachmentSources(teamId: String) → AttachmentSourcesPayload
[Internal] Get a list of all unique attachment sources in the workspace.

### applicationInfo(clientId: NON_NULL) → Application
Get basic information for an application.

### agentSessions(before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → AgentSessionConnection
All agent sessions.

### agentSession(id: NON_NULL) → AgentSession
A specific agent session.

### agentSessionSandbox(agentSessionId: NON_NULL) → CodingAgentSandboxPayload
[Internal] Retrieves the coding agent sandbox for a given agent session ID.

### agentActivities(filter: AgentActivityFilter, before: String, after: String, first: Int, last: Int, includeArchived: Boolean, orderBy: PaginationOrderBy) → AgentActivityConnection
All agent activities.

### agentActivity(id: NON_NULL) → AgentActivity
A specific agent activity.


## Mutations

### fileUpload(metaData: JSON, makePublic: Boolean, size: NON_NULL, contentType: NON_NULL, filename: NON_NULL) → UploadPayload
XHR request payload to upload an images, video and other attachments directly to Linear's cloud storage.

### importFileUpload(metaData: JSON, size: NON_NULL, contentType: NON_NULL, filename: NON_NULL) → UploadPayload
XHR request payload to upload a file for import, directly to Linear's cloud storage.

### imageUploadFromUrl(url: NON_NULL) → ImageUploadFromUrlPayload
Upload an image from an URL to Linear.

### fileUploadDangerouslyDelete(assetUrl: NON_NULL) → FileUploadDeletePayload
[INTERNAL] Permanently delete an uploaded file by asset URL. This should be used as a last resort and will break comments and documents that reference the asset.

### workflowStateCreate(input: NON_NULL) → WorkflowStatePayload
Creates a new state, adding it to the workflow of a team.

### workflowStateUpdate(input: NON_NULL, id: NON_NULL) → WorkflowStatePayload
Updates a state.

### workflowStateArchive(id: NON_NULL) → WorkflowStateArchivePayload
Archives a state. Only states with issues that have all been archived can be archived.

### webhookCreate(input: NON_NULL) → WebhookPayload
Creates a new webhook.

### webhookUpdate(input: NON_NULL, id: NON_NULL) → WebhookPayload
Updates an existing Webhook.

### webhookDelete(id: NON_NULL) → DeletePayload
Deletes a Webhook.

### webhookRotateSecret(id: NON_NULL) → WebhookRotateSecretPayload
Rotates the signing secret for a Webhook.

### viewPreferencesCreate(input: NON_NULL) → ViewPreferencesPayload
Creates a new ViewPreferences object.

### viewPreferencesUpdate(input: NON_NULL, id: NON_NULL) → ViewPreferencesPayload
Updates an existing ViewPreferences object.

### viewPreferencesDelete(id: NON_NULL) → DeletePayload
Deletes a ViewPreferences.

### userSettingsUpdate(input: NON_NULL, id: NON_NULL) → UserSettingsPayload
Updates the user's settings.

### userSettingsFlagsReset(flags: LIST) → UserSettingsFlagsResetPayload
Resets user's setting flags.

### userFlagUpdate(operation: NON_NULL, flag: NON_NULL) → UserSettingsFlagPayload
Updates a user's settings flag.

### notificationCategoryChannelSubscriptionUpdate(channel: NON_NULL, category: NON_NULL, subscribe: NON_NULL) → UserSettingsPayload
Subscribes to or unsubscribes from a notification category for a given notification channel for the user

### userUpdate(input: NON_NULL, id: NON_NULL) → UserPayload
Updates a user. Only available to organization admins and the user themselves.

### userDiscordConnect(redirectUri: NON_NULL, code: NON_NULL) → UserPayload
Connects the Discord user to this Linear account via OAuth2.

### userExternalUserDisconnect(service: NON_NULL) → UserPayload
Disconnects the external user from this Linear account.

### userChangeRole(role: NON_NULL, id: NON_NULL) → UserAdminPayload
Changes the role of a user.

### userSuspend(forceBypassScimRestrictions: Boolean, id: NON_NULL) → UserAdminPayload
Suspends a user. Can only be called by an admin or owner.

### userRevokeAllSessions(id: NON_NULL) → UserAdminPayload
Revokes a user's sessions. Can only be called by an admin or owner.

### userRevokeSession(sessionId: NON_NULL, id: NON_NULL) → UserAdminPayload
Revokes a specific session for a user. Can only be called by an admin or owner.

### userUnsuspend(forceBypassScimRestrictions: Boolean, id: NON_NULL) → UserAdminPayload
Un-suspends a user. Can only be called by an admin or owner.

### userUnlinkFromIdentityProvider(id: NON_NULL) → UserAdminPayload
Unlinks a guest user from their identity provider. Can only be called by an admin when SCIM is enabled.

### triageResponsibilityCreate(input: NON_NULL) → TriageResponsibilityPayload
Creates a new triage responsibility.

### triageResponsibilityUpdate(input: NON_NULL, id: NON_NULL) → TriageResponsibilityPayload
Updates an existing triage responsibility.

### triageResponsibilityDelete(id: NON_NULL) → DeletePayload
Deletes a triage responsibility.

### timeScheduleCreate(input: NON_NULL) → TimeSchedulePayload
Creates a new time schedule.

### timeScheduleUpdate(input: NON_NULL, id: NON_NULL) → TimeSchedulePayload
Updates a time schedule.

### timeScheduleUpsertExternal(input: NON_NULL, externalId: NON_NULL) → TimeSchedulePayload
Upsert an external time schedule.

### timeScheduleDelete(id: NON_NULL) → DeletePayload
Deletes a time schedule.

### timeScheduleRefreshIntegrationSchedule(id: NON_NULL) → TimeSchedulePayload
Refresh the integration schedule information.

### templateCreate(input: NON_NULL) → TemplatePayload
Creates a new template.

### templateUpdate(input: NON_NULL, id: NON_NULL) → TemplatePayload
Updates an existing template.

### templateDelete(id: NON_NULL) → DeletePayload
Deletes a template.

### projectCreate(slackChannelName: String, input: NON_NULL) → ProjectPayload
Creates a new project.

### projectUpdate(input: NON_NULL, id: NON_NULL) → ProjectPayload
Updates a project.

### projectReassignStatus(newProjectStatusId: NON_NULL, originalProjectStatusId: NON_NULL) → SuccessPayload
[INTERNAL] Updates all projects currently assigned to to a project status to a new project status.

### projectDelete(id: NON_NULL) → ProjectArchivePayload
Deletes (trashes) a project.

### projectUnarchive(id: NON_NULL) → ProjectArchivePayload
Unarchives a project.

### projectAddLabel(labelId: NON_NULL, id: NON_NULL) → ProjectPayload
Adds a label to a project.

### projectRemoveLabel(labelId: NON_NULL, id: NON_NULL) → ProjectPayload
Removes a label from a project.

### projectExternalSyncDisable(syncSource: NON_NULL, projectId: NON_NULL) → ProjectPayload
Disables external sync on a project.

### teamCreate(copySettingsFromTeamId: String, input: NON_NULL) → TeamPayload
Creates a new team. The user who creates the team will automatically be added as a member to the newly created team.

### teamUpdate(mapping: InheritanceEntityMapping, input: NON_NULL, id: NON_NULL) → TeamPayload
Updates a team.

### teamDelete(id: NON_NULL) → DeletePayload
Deletes a team.

### teamUnarchive(id: NON_NULL) → TeamArchivePayload
Unarchives a team and cancels deletion.

### teamCyclesDelete(id: NON_NULL) → TeamPayload
Deletes team's cycles data

### teamMembershipCreate(input: NON_NULL) → TeamMembershipPayload
Creates a new team membership.

### teamMembershipUpdate(input: NON_NULL, id: NON_NULL) → TeamMembershipPayload
Updates a team membership.

### teamMembershipDelete(alsoLeaveParentTeams: Boolean, id: NON_NULL) → DeletePayload
Deletes a team membership.

### teamKeyDelete(id: NON_NULL) → DeletePayload
Deletes a previously used team key.

### roadmapToProjectCreate(input: NON_NULL) → RoadmapToProjectPayload
Creates a new roadmapToProject join.

### roadmapToProjectUpdate(input: NON_NULL, id: NON_NULL) → RoadmapToProjectPayload
Updates a roadmapToProject.

### roadmapToProjectDelete(id: NON_NULL) → DeletePayload
Deletes a roadmapToProject.

### createCsvExportReport(includePrivateTeamIds: LIST) → CreateCsvExportReportPayload
Create CSV export report for the organization.

### releaseStageCreate(input: NON_NULL) → ReleaseStagePayload
[ALPHA] Creates a new release stage.

### releaseStageUpdate(input: NON_NULL, id: NON_NULL) → ReleaseStagePayload
[ALPHA] Updates a release stage.

### releaseStageArchive(id: NON_NULL) → ReleaseStageArchivePayload
[ALPHA] Archives a release stage.

### releaseStageUnarchive(id: NON_NULL) → ReleaseStageArchivePayload
[ALPHA] Unarchives a release stage.

### releaseSync(input: NON_NULL) → ReleasePayload
[ALPHA] Syncs release data.

### releaseCreate(input: NON_NULL) → ReleasePayload
[ALPHA] Creates a new release.

### releaseUpdate(input: NON_NULL, id: NON_NULL) → ReleasePayload
[ALPHA] Updates a release.

### releaseComplete(input: NON_NULL) → ReleasePayload
[ALPHA] Marks a release as completed. If version is provided, completes that specific release; otherwise completes the most recent started release.

### releaseUpdateByPipeline(input: NON_NULL) → ReleasePayload
[ALPHA] Updates a release by pipeline.

### releaseDelete(id: NON_NULL) → DeletePayload
[ALPHA] Deletes a release.

### releaseArchive(id: NON_NULL) → ReleaseArchivePayload
[ALPHA] Archives a release.

### releaseUnarchive(id: NON_NULL) → ReleaseArchivePayload
[ALPHA] Unarchives a release.

### releaseSyncByAccessKey(input: NON_NULL) → ReleasePayload
[ALPHA] Syncs release data using an access key. The pipeline is inferred from the access key.

### releaseCompleteByAccessKey(input: NON_NULL) → ReleasePayload
[ALPHA] Marks a release as completed using an access key. If version is provided, completes that specific release; otherwise completes the most recent started release. The pipeline is inferred from the access key.

### releaseUpdateByPipelineByAccessKey(input: NON_NULL) → ReleasePayload
[ALPHA] Updates a release by pipeline using an access key.

### releasePipelineCreate(input: NON_NULL) → ReleasePipelinePayload
[ALPHA] Creates a new release pipeline.

### releasePipelineUpdate(input: NON_NULL, id: NON_NULL) → ReleasePipelinePayload
[ALPHA] Updates a release pipeline.

### releasePipelineArchive(id: NON_NULL) → ReleasePipelineArchivePayload
[ALPHA] Archives a release pipeline.

### releasePipelineUnarchive(id: NON_NULL) → ReleasePipelineArchivePayload
[ALPHA] Unarchives a release pipeline.

### releasePipelineDelete(id: NON_NULL) → DeletePayload
[ALPHA] Deletes a release pipeline.

### reactionCreate(input: NON_NULL) → ReactionPayload
Creates a new reaction.

### reactionDelete(id: NON_NULL) → DeletePayload
Deletes a reaction.

### pushSubscriptionCreate(input: NON_NULL) → PushSubscriptionPayload
Creates a push subscription.

### pushSubscriptionDelete(id: NON_NULL) → PushSubscriptionPayload
Deletes a push subscription.

### projectUpdateCreate(input: NON_NULL) → ProjectUpdatePayload
Creates a new project update.

### projectUpdateUpdate(input: NON_NULL, id: NON_NULL) → ProjectUpdatePayload
Updates a project update.

### projectUpdateArchive(id: NON_NULL) → ProjectUpdateArchivePayload
Archives a project update.

### projectUpdateUnarchive(id: NON_NULL) → ProjectUpdateArchivePayload
Unarchives a project update.

### createProjectUpdateReminder(userId: String, projectId: NON_NULL) → ProjectUpdateReminderPayload
Create a notification to remind a user about a project update.

### projectStatusCreate(input: NON_NULL) → ProjectStatusPayload
Creates a new project status.

### projectStatusUpdate(input: NON_NULL, id: NON_NULL) → ProjectStatusPayload
Updates a project status.

### projectStatusArchive(id: NON_NULL) → ProjectStatusArchivePayload
Archives a project status.

### projectStatusUnarchive(id: NON_NULL) → ProjectStatusArchivePayload
Unarchives a project status.

### projectRelationCreate(input: NON_NULL) → ProjectRelationPayload
Creates a new project relation.

### projectRelationUpdate(input: NON_NULL, id: NON_NULL) → ProjectRelationPayload
Updates a project relation.

### projectRelationDelete(id: NON_NULL) → DeletePayload
Deletes a project relation.

### projectMilestoneCreate(input: NON_NULL) → ProjectMilestonePayload
Creates a new project milestone.

### projectMilestoneUpdate(input: NON_NULL, id: NON_NULL) → ProjectMilestonePayload
Updates a project milestone.

### projectMilestoneDelete(id: NON_NULL) → DeletePayload
Deletes a project milestone.

### projectMilestoneMove(input: NON_NULL, id: NON_NULL) → ProjectMilestoneMovePayload
[Internal] Moves a project milestone to another project, can be called to undo a prior move.

### projectLabelCreate(input: NON_NULL) → ProjectLabelPayload
Creates a new project label.

### projectLabelUpdate(input: NON_NULL, id: NON_NULL) → ProjectLabelPayload
Updates a project label.

### projectLabelDelete(id: NON_NULL) → DeletePayload
Deletes a project label.

### projectLabelRetire(id: NON_NULL) → ProjectLabelPayload
Retires a project label.

### projectLabelRestore(id: NON_NULL) → ProjectLabelPayload
Restores a project label.

### organizationUpdate(input: NON_NULL) → OrganizationPayload
Updates the user's organization.

### organizationDeleteChallenge() → OrganizationDeletePayload
Get an organization's delete confirmation token.

### organizationDelete(input: NON_NULL) → OrganizationDeletePayload
Deletes an organization.

### organizationCancelDelete() → OrganizationCancelDeletePayload
Cancels the deletion of an organization.

### organizationStartTrialForPlan(input: NON_NULL) → OrganizationStartTrialPayload
Starts a trial for the organization on the specified plan type.

### organizationInviteCreate(input: NON_NULL) → OrganizationInvitePayload
Creates a new organization invite.

### organizationInviteUpdate(input: NON_NULL, id: NON_NULL) → OrganizationInvitePayload
Updates an organization invite.

### resendOrganizationInvite(id: NON_NULL) → DeletePayload
Re-send an organization invite.

### resendOrganizationInviteByEmail(email: NON_NULL) → DeletePayload
Re-send an organization invite tied to an email address.

### organizationInviteDelete(id: NON_NULL) → DeletePayload
Deletes an organization invite.

### organizationDomainClaim(id: NON_NULL) → OrganizationDomainSimplePayload
[INTERNAL] Verifies a domain claim.

### organizationDomainVerify(input: NON_NULL) → OrganizationDomainPayload
[INTERNAL] Verifies a domain to be added to an organization.

### organizationDomainCreate(triggerEmailVerification: Boolean, input: NON_NULL) → OrganizationDomainPayload
[INTERNAL] Adds a domain to be allowed for an organization.

### organizationDomainUpdate(input: NON_NULL, id: NON_NULL) → OrganizationDomainPayload
[INTERNAL] Updates an organization domain settings.

### organizationDomainDelete(id: NON_NULL) → DeletePayload
Deletes a domain.

### notificationSubscriptionCreate(input: NON_NULL) → NotificationSubscriptionPayload
Creates a new notification subscription for a cycle, custom view, label, project or team.

### notificationSubscriptionUpdate(input: NON_NULL, id: NON_NULL) → NotificationSubscriptionPayload
Updates a notification subscription.

### notificationUpdate(input: NON_NULL, id: NON_NULL) → NotificationPayload
Updates a notification.

### notificationMarkReadAll(readAt: NON_NULL, input: NON_NULL) → NotificationBatchActionPayload
Marks notification and all related notifications as read.

### notificationMarkUnreadAll(input: NON_NULL) → NotificationBatchActionPayload
Marks notification and all related notifications as unread.

### notificationSnoozeAll(snoozedUntilAt: NON_NULL, input: NON_NULL) → NotificationBatchActionPayload
Snoozes a notification and all related notifications.

### notificationUnsnoozeAll(unsnoozedAt: NON_NULL, input: NON_NULL) → NotificationBatchActionPayload
Unsnoozes a notification and all related notifications.

### notificationArchive(id: NON_NULL) → NotificationArchivePayload
Archives a notification.

### notificationArchiveAll(input: NON_NULL) → NotificationBatchActionPayload
Archives a notification and all related notifications.

### notificationUnarchive(id: NON_NULL) → NotificationArchivePayload
Unarchives a notification.

### issueToReleaseCreate(input: NON_NULL) → IssueToReleasePayload
[ALPHA] Creates a new issueToRelease join, adding an issue to a release.

### issueToReleaseDeleteByIssueAndRelease(releaseId: NON_NULL, issueId: NON_NULL) → DeletePayload
[ALPHA] Deletes an issueToRelease by issue and release identifiers

### issueToReleaseDelete(id: NON_NULL) → DeletePayload
[ALPHA] Deletes an issueToRelease by its identifier, removing an issue from a release.

### issueCreate(input: NON_NULL) → IssuePayload
Creates a new issue.

### issueBatchCreate(input: NON_NULL) → IssueBatchPayload
Creates a list of issues in one transaction.

### issueUpdate(input: NON_NULL, id: NON_NULL) → IssuePayload
Updates an issue.

### issueBatchUpdate(input: NON_NULL, ids: NON_NULL) → IssueBatchPayload
Updates multiple issues at once.

### issueArchive(trash: Boolean, id: NON_NULL) → IssueArchivePayload
Archives an issue.

### issueUnarchive(id: NON_NULL) → IssueArchivePayload
Unarchives an issue.

### issueDelete(permanentlyDelete: Boolean, id: NON_NULL) → IssueArchivePayload
Deletes (trashes) an issue.

### issueAddLabel(labelId: NON_NULL, id: NON_NULL) → IssuePayload
Adds a label to an issue.

### issueRemoveLabel(labelId: NON_NULL, id: NON_NULL) → IssuePayload
Removes a label from an issue.

### issueReminder(reminderAt: NON_NULL, id: NON_NULL) → IssuePayload
Adds an issue reminder. Will cause a notification to be sent when the issue reminder time is reached.

### issueSubscribe(userEmail: String, userId: String, id: NON_NULL) → IssuePayload
Subscribes a user to an issue.

### issueUnsubscribe(userEmail: String, userId: String, id: NON_NULL) → IssuePayload
Unsubscribes a user from an issue.

### issueDescriptionUpdateFromFront(description: NON_NULL, id: NON_NULL) → IssuePayload
[INTERNAL] Updates an issue description from the Front app to handle Front attachments correctly.

### issueExternalSyncDisable(attachmentId: NON_NULL) → IssuePayload
Disables external sync on an issue.

### issueRelationCreate(overrideCreatedAt: DateTime, input: NON_NULL) → IssueRelationPayload
Creates a new issue relation.

### issueRelationUpdate(input: NON_NULL, id: NON_NULL) → IssueRelationPayload
Updates an issue relation.

### issueRelationDelete(id: NON_NULL) → DeletePayload
Deletes an issue relation.

### issueLabelCreate(replaceTeamLabels: Boolean, input: NON_NULL) → IssueLabelPayload
Creates a new label.

### issueLabelUpdate(replaceTeamLabels: Boolean, input: NON_NULL, id: NON_NULL) → IssueLabelPayload
Updates a label.

### issueLabelDelete(id: NON_NULL) → DeletePayload
Deletes an issue label.

### issueLabelRetire(id: NON_NULL) → IssueLabelPayload
Retires a label.

### issueLabelRestore(id: NON_NULL) → IssueLabelPayload
Restores a label.

### issueImportCreateGithub(teamId: String, teamName: String, githubRepoIds: LIST, githubLabels: LIST, instantProcess: Boolean, includeClosedIssues: Boolean) → IssueImportPayload
Kicks off a GitHub import job.

### issueImportCreateJira(teamId: String, teamName: String, jiraToken: NON_NULL, jiraProject: NON_NULL, jiraEmail: NON_NULL, jiraHostname: NON_NULL, jql: String, instantProcess: Boolean, includeClosedIssues: Boolean, id: String) → IssueImportPayload
Kicks off a Jira import job.

### issueImportCreateCSVJira(teamId: String, teamName: String, csvUrl: NON_NULL, jiraHostname: String, jiraToken: String, jiraEmail: String) → IssueImportPayload
Kicks off a Jira import job from a CSV.

### issueImportCreateClubhouse(teamId: String, teamName: String, clubhouseToken: NON_NULL, clubhouseGroupName: NON_NULL, instantProcess: Boolean, includeClosedIssues: Boolean, id: String) → IssueImportPayload
Kicks off a Shortcut (formerly Clubhouse) import job.

### issueImportCreateAsana(teamId: String, teamName: String, asanaToken: NON_NULL, asanaTeamName: NON_NULL, instantProcess: Boolean, includeClosedIssues: Boolean, id: String) → IssueImportPayload
Kicks off an Asana import job.

### issueImportCreateLinearV2(linearSourceOrganizationId: NON_NULL, id: String) → IssueImportPayload
[INTERNAL] Kicks off a Linear to Linear import job.

### issueImportDelete(issueImportId: NON_NULL) → IssueImportDeletePayload
Deletes an import job.

### issueImportProcess(mapping: NON_NULL, issueImportId: NON_NULL) → IssueImportPayload
Kicks off import processing.

### issueImportUpdate(input: NON_NULL, id: NON_NULL) → IssueImportPayload
Updates the mapping for the issue import.

### integrationsSettingsCreate(input: NON_NULL) → IntegrationsSettingsPayload
Creates new settings for one or more integrations.

### integrationsSettingsUpdate(input: NON_NULL, id: NON_NULL) → IntegrationsSettingsPayload
Updates settings related to integrations for a project or a team.

### integrationTemplateCreate(input: NON_NULL) → IntegrationTemplatePayload
Creates a new integrationTemplate join.

### integrationTemplateDelete(id: NON_NULL) → DeletePayload
Deletes a integrationTemplate.

### integrationUpdate(input: NON_NULL, id: NON_NULL) → IntegrationPayload
[INTERNAL] Updates the integration.

### integrationGithubCommitCreate() → GitHubCommitIntegrationPayload
Generates a webhook for the GitHub commit integration.

### integrationGithubConnect(githubHost: String, codeAccess: Boolean, code: NON_NULL, installationId: NON_NULL) → IntegrationPayload
Connects the organization with the GitHub App.

### integrationGithubImportConnect(code: NON_NULL, installationId: NON_NULL) → IntegrationPayload
Connects the organization with the GitHub Import App.

### integrationGithubImportRefresh(id: NON_NULL) → IntegrationPayload
Refreshes the data for a GitHub import integration.

### integrationGitHubEnterpriseServerConnect(organizationName: NON_NULL, githubUrl: NON_NULL) → GitHubEnterpriseServerPayload
Connects the organization with a GitHub Enterprise Server.

### integrationGitlabConnect(gitlabUrl: NON_NULL, accessToken: NON_NULL) → GitLabIntegrationCreatePayload
Connects the organization with a GitLab Access Token.

### integrationGitlabTestConnection(integrationId: NON_NULL) → GitLabTestConnectionPayload
Tests connectivity to a self-hosted GitLab instance and clears auth errors if successful.

### airbyteIntegrationConnect(input: NON_NULL) → IntegrationPayload
Creates an integration api key for Airbyte to connect with Linear.

### integrationGoogleCalendarPersonalConnect(code: NON_NULL) → IntegrationPayload
[Internal] Connects the Google Calendar to the user to this Linear account via OAuth2.

### integrationLaunchDarklyConnect(code: NON_NULL, projectKey: NON_NULL, environment: NON_NULL) → IntegrationPayload
[INTERNAL] Integrates the organization with LaunchDarkly.

### integrationLaunchDarklyPersonalConnect(code: NON_NULL) → IntegrationPayload
[INTERNAL] Integrates your personal account with LaunchDarkly.

### jiraIntegrationConnect(input: NON_NULL) → IntegrationPayload
[INTERNAL] Connects the organization with a Jira Personal Access Token.

### integrationJiraUpdate(input: NON_NULL) → IntegrationPayload
[INTERNAL] Updates a Jira Integration.

### integrationJiraFetchProjectStatuses(input: NON_NULL) → JiraFetchProjectStatusesPayload
[INTERNAL] Fetches Jira project statuses and stores them in integration settings.

### integrationJiraPersonal(code: String, accessToken: String) → IntegrationPayload
Connect your Jira account to Linear.

### integrationGitHubPersonal(codeAccess: Boolean, code: NON_NULL) → IntegrationPayload
Connect your GitHub account to Linear.

### integrationIntercom(domainUrl: String, redirectUri: NON_NULL, code: NON_NULL) → IntegrationPayload
Integrates the organization with Intercom.

### integrationIntercomDelete() → IntegrationPayload
Disconnects the organization from Intercom.

### integrationCustomerDataAttributesRefresh(input: NON_NULL) → IntegrationPayload
[INTERNAL] Refreshes the customer data attributes from the specified integration service.

### integrationDiscord(redirectUri: NON_NULL, code: NON_NULL) → IntegrationPayload
Integrates the organization with Discord.

### integrationOpsgenieConnect(apiKey: NON_NULL) → IntegrationPayload
[INTERNAL] Integrates the organization with Opsgenie.

### integrationOpsgenieRefreshScheduleMappings() → IntegrationPayload
[INTERNAL] Refresh Opsgenie schedule mappings.

### integrationPagerDutyConnect(code: NON_NULL, redirectUri: NON_NULL) → IntegrationPayload
[INTERNAL] Integrates the organization with PagerDuty.

### integrationPagerDutyRefreshScheduleMappings() → IntegrationPayload
[INTERNAL] Refresh PagerDuty schedule mappings.

### updateIntegrationSlackScopes(integrationId: NON_NULL, redirectUri: NON_NULL, code: NON_NULL) → IntegrationPayload
[Internal] Updates existing Slack integration scopes.

### integrationSlack(shouldUseV2Auth: Boolean, redirectUri: NON_NULL, code: NON_NULL) → IntegrationPayload
Integrates the organization with Slack.

### integrationSlackAsks(redirectUri: NON_NULL, code: NON_NULL) → IntegrationPayload
Integrates the organization with the Slack Asks app.

### integrationSlackOrAsksUpdateSlackTeamName(integrationId: NON_NULL) → IntegrationSlackWorkspaceNamePayload
Updates the Slack team's name in Linear for an existing Slack or Asks integration.

### integrationSlackPersonal(redirectUri: NON_NULL, code: NON_NULL) → IntegrationPayload
Integrates your personal notifications with Slack.

### integrationAsksConnectChannel(redirectUri: NON_NULL, code: NON_NULL) → AsksChannelConnectPayload
Connect a Slack channel to Asks.

### integrationSlackPost(shouldUseV2Auth: Boolean, redirectUri: NON_NULL, teamId: NON_NULL, code: NON_NULL) → SlackChannelConnectPayload
Slack integration for team notifications.

### integrationSlackProjectPost(service: NON_NULL, redirectUri: NON_NULL, projectId: NON_NULL, code: NON_NULL) → SlackChannelConnectPayload
Slack integration for project notifications.

### integrationSlackInitiativePost(redirectUri: NON_NULL, initiativeId: NON_NULL, code: NON_NULL) → SlackChannelConnectPayload
[Internal] Slack integration for initiative notifications.

### integrationSlackCustomViewNotifications(redirectUri: NON_NULL, customViewId: NON_NULL, code: NON_NULL) → SlackChannelConnectPayload
Slack integration for custom view notifications.

### integrationSlackCustomerChannelLink(redirectUri: NON_NULL, customerId: NON_NULL, code: NON_NULL) → SuccessPayload
Integrates a Slack Asks channel with a Customer.

### integrationSlackOrgProjectUpdatesPost(redirectUri: NON_NULL, code: NON_NULL) → SlackChannelConnectPayload
Slack integration for organization level project update notifications.

### integrationSlackOrgInitiativeUpdatesPost(redirectUri: NON_NULL, code: NON_NULL) → SlackChannelConnectPayload
[Internal] Slack integration for organization level initiative update notifications.

### integrationSlackImportEmojis(redirectUri: NON_NULL, code: NON_NULL) → IntegrationPayload
Imports custom emojis from your Slack workspace.

### integrationFigma(redirectUri: NON_NULL, code: NON_NULL) → IntegrationPayload
Integrates the organization with Figma.

### integrationGong(redirectUri: NON_NULL, code: NON_NULL) → IntegrationPayload
Integrates the organization with Gong.

### integrationMicrosoftTeams(redirectUri: NON_NULL, code: NON_NULL) → IntegrationPayload
[ALPHA] Integrates the organization with Microsoft Teams.

### integrationMicrosoftPersonalConnect(redirectUri: NON_NULL, code: NON_NULL) → IntegrationPayload
[ALPHA] Connects the user's personal Microsoft account to Linear.

### integrationGoogleSheets(code: NON_NULL) → IntegrationPayload
Integrates the organization with Google Sheets.

### refreshGoogleSheetsData(type: String, id: NON_NULL) → IntegrationPayload
Manually update Google Sheets data.

### integrationSentryConnect(organizationSlug: NON_NULL, code: NON_NULL, installationId: NON_NULL) → IntegrationPayload
Integrates the organization with Sentry.

### integrationFront(redirectUri: NON_NULL, code: NON_NULL) → IntegrationPayload
Integrates the organization with Front.

### integrationZendesk(subdomain: NON_NULL, code: NON_NULL, scope: NON_NULL, redirectUri: NON_NULL) → IntegrationPayload
Integrates the organization with Zendesk.

### integrationSalesforce(code: NON_NULL, subdomain: NON_NULL, redirectUri: NON_NULL) → IntegrationPayload
Integrates the organization with Salesforce.

### integrationSalesforceMetadataRefresh(id: NON_NULL) → IntegrationPayload
[INTERNAL] Refreshes the Salesforce integration metadata.

### integrationMcpServerPersonalConnect(serverUrl: NON_NULL) → IntegrationPayload
[INTERNAL] Connects the user's personal account with an MCP server.

### integrationMcpServerConnect(teamId: String, serverUrl: NON_NULL) → IntegrationPayload
[INTERNAL] Connects the workspace with an MCP server.

### integrationDelete(skipInstallationDeletion: Boolean, id: NON_NULL) → DeletePayload
Deletes an integration.

### integrationArchive(id: NON_NULL) → DeletePayload
Archives an integration.

### integrationSlackWorkflowAccessUpdate(enabled: NON_NULL, integrationId: NON_NULL) → IntegrationPayload
[Internal] Enables Linear Agent Slack workflow access for a Slack or Slack Asks integration.

### integrationRequest(input: NON_NULL) → IntegrationRequestPayload
Requests a currently unavailable integration.

### initiativeUpdateCreate(input: NON_NULL) → InitiativeUpdatePayload
Creates a initiative update.

### initiativeUpdateUpdate(input: NON_NULL, id: NON_NULL) → InitiativeUpdatePayload
Updates an update.

### initiativeUpdateArchive(id: NON_NULL) → InitiativeUpdateArchivePayload
Archives an initiative update.

### createInitiativeUpdateReminder(userId: String, initiativeId: NON_NULL) → InitiativeUpdateReminderPayload
Create a notification to remind a user about an initiative update.

### initiativeUpdateUnarchive(id: NON_NULL) → InitiativeUpdateArchivePayload
Unarchives an initiative update.

### initiativeToProjectCreate(input: NON_NULL) → InitiativeToProjectPayload
Creates a new initiativeToProject join.

### initiativeToProjectUpdate(input: NON_NULL, id: NON_NULL) → InitiativeToProjectPayload
Updates a initiativeToProject.

### initiativeToProjectDelete(id: NON_NULL) → DeletePayload
Deletes a initiativeToProject.

### initiativeCreate(input: NON_NULL) → InitiativePayload
Creates a new initiative.

### initiativeUpdate(input: NON_NULL, id: NON_NULL) → InitiativePayload
Updates a initiative.

### initiativeArchive(id: NON_NULL) → InitiativeArchivePayload
Archives a initiative.

### initiativeUnarchive(id: NON_NULL) → InitiativeArchivePayload
Unarchives a initiative.

### initiativeDelete(id: NON_NULL) → DeletePayload
Deletes (trashes) an initiative.

### initiativeRelationCreate(input: NON_NULL) → InitiativeRelationPayload
Creates a new initiative relation.

### initiativeRelationUpdate(input: NON_NULL, id: NON_NULL) → DeletePayload
Updates an initiative relation.

### initiativeRelationDelete(id: NON_NULL) → DeletePayload
Deletes an initiative relation.

### gitAutomationTargetBranchCreate(input: NON_NULL) → GitAutomationTargetBranchPayload
Creates a Git target branch automation.

### gitAutomationTargetBranchUpdate(input: NON_NULL, id: NON_NULL) → GitAutomationTargetBranchPayload
Updates an existing Git target branch automation.

### gitAutomationTargetBranchDelete(id: NON_NULL) → DeletePayload
Archives a Git target branch automation.

### gitAutomationStateCreate(input: NON_NULL) → GitAutomationStatePayload
Creates a new automation state.

### gitAutomationStateUpdate(input: NON_NULL, id: NON_NULL) → GitAutomationStatePayload
Updates an existing state.

### gitAutomationStateDelete(id: NON_NULL) → DeletePayload
Archives an automation state.

### favoriteCreate(input: NON_NULL) → FavoritePayload
Creates a new favorite (project, cycle etc).

### favoriteUpdate(input: NON_NULL, id: NON_NULL) → FavoritePayload
Updates a favorite.

### favoriteDelete(id: NON_NULL) → DeletePayload
Deletes a favorite reference.

### trackAnonymousEvent(input: NON_NULL) → EventTrackingPayload
Track an anonymous analytics event.

### entityExternalLinkCreate(input: NON_NULL) → EntityExternalLinkPayload
Creates a new entity link.

### entityExternalLinkUpdate(input: NON_NULL, id: NON_NULL) → EntityExternalLinkPayload
Updates an entity link.

### entityExternalLinkDelete(id: NON_NULL) → DeletePayload
Deletes an entity link.

### emojiCreate(input: NON_NULL) → EmojiPayload
Creates a custom emoji.

### emojiDelete(id: NON_NULL) → DeletePayload
Deletes an emoji.

### emailUnsubscribe(input: NON_NULL) → EmailUnsubscribePayload
Unsubscribes the user from one type of email.

### emailIntakeAddressCreate(input: NON_NULL) → EmailIntakeAddressPayload
Creates a new email intake address.

### emailIntakeAddressRotate(id: NON_NULL) → EmailIntakeAddressPayload
Rotates an existing email intake address.

### emailIntakeAddressUpdate(input: NON_NULL, id: NON_NULL) → EmailIntakeAddressPayload
Updates an existing email intake address.

### emailIntakeAddressDelete(id: NON_NULL) → DeletePayload
Deletes an email intake address object.

### documentCreate(input: NON_NULL) → DocumentPayload
Creates a new document.

### documentUpdate(input: NON_NULL, id: NON_NULL) → DocumentPayload
Updates a document.

### documentDelete(id: NON_NULL) → DocumentArchivePayload
Deletes (trashes) a document.

### documentUnarchive(id: NON_NULL) → DocumentArchivePayload
Restores a document.

### cycleCreate(input: NON_NULL) → CyclePayload
Creates a new cycle.

### cycleUpdate(input: NON_NULL, id: NON_NULL) → CyclePayload
Updates a cycle.

### cycleArchive(id: NON_NULL) → CycleArchivePayload
Archives a cycle.

### cycleShiftAll(input: NON_NULL) → CyclePayload
Shifts all cycles starts and ends by a certain number of days, starting from the provided cycle onwards.

### cycleStartUpcomingCycleToday(id: NON_NULL) → CyclePayload
Shifts all cycles starts and ends by a certain number of days, starting from the provided cycle onwards.

### customerTierCreate(input: NON_NULL) → CustomerTierPayload
Creates a new customer tier.

### customerTierUpdate(input: NON_NULL, id: NON_NULL) → CustomerTierPayload
Updates a customer tier.

### customerTierDelete(id: NON_NULL) → DeletePayload
Deletes a customer tier.

### customerStatusCreate(input: NON_NULL) → CustomerStatusPayload
Creates a new customer status.

### customerStatusUpdate(input: NON_NULL, id: NON_NULL) → CustomerStatusPayload
Updates a customer status.

### customerStatusDelete(id: NON_NULL) → DeletePayload
Deletes a customer status.

### customerCreate(input: NON_NULL) → CustomerPayload
Creates a new customer.

### customerUpdate(input: NON_NULL, id: NON_NULL) → CustomerPayload
Updates a customer

### customerDelete(id: NON_NULL) → DeletePayload
Deletes a customer.

### customerMerge(sourceCustomerId: NON_NULL, targetCustomerId: NON_NULL) → CustomerPayload
Merges two customers.

### customerUpsert(input: NON_NULL) → CustomerPayload
Upserts a customer, creating it if it doesn't exists, updating it otherwise. Matches against an existing customer with `id` or `externalId`

### customerUnsync(id: NON_NULL) → CustomerPayload
Unsyncs a managed customer from the its current data source. External IDs mapping to the external source will be cleared.

### customerNeedCreate(input: NON_NULL) → CustomerNeedPayload
Creates a new customer need.

### customerNeedCreateFromAttachment(input: NON_NULL) → CustomerNeedPayload
Creates a new customer need out of an attachment

### customerNeedUpdate(input: NON_NULL, id: NON_NULL) → CustomerNeedUpdatePayload
Updates a customer need

### customerNeedDelete(keepAttachment: Boolean, id: NON_NULL) → DeletePayload
Deletes a customer need.

### customerNeedArchive(id: NON_NULL) → CustomerNeedArchivePayload
Archives a customer need.

### customerNeedUnarchive(id: NON_NULL) → CustomerNeedArchivePayload
Unarchives a customer need.

### customViewCreate(input: NON_NULL) → CustomViewPayload
Creates a new custom view.

### customViewUpdate(input: NON_NULL, id: NON_NULL) → CustomViewPayload
Updates a custom view.

### customViewDelete(id: NON_NULL) → DeletePayload
Deletes a custom view.

### contactCreate(input: NON_NULL) → ContactPayload
Saves user message.

### contactSalesCreate(input: NON_NULL) → ContactPayload
[INTERNAL] Saves sales pricing inquiry to Front.

### commentCreate(input: NON_NULL) → CommentPayload
Creates a new comment.

### commentUpdate(skipEditedAt: Boolean, input: NON_NULL, id: NON_NULL) → CommentPayload
Updates a comment.

### commentDelete(id: NON_NULL) → DeletePayload
Deletes a comment.

### commentResolve(resolvingCommentId: String, id: NON_NULL) → CommentPayload
Resolves a comment.

### commentUnresolve(id: NON_NULL) → CommentPayload
Unresolves a comment.

### emailUserAccountAuthChallenge(input: NON_NULL) → EmailUserAccountAuthChallengeResponse
Finds or creates a new user account by email and sends an email with token.

### emailTokenUserAccountAuth(input: NON_NULL) → AuthResolverResponse
Authenticates a user account via email and authentication token.

### samlTokenUserAccountAuth(input: NON_NULL) → AuthResolverResponse
Authenticates a user account via email and authentication token for SAML.

### googleUserAccountAuth(input: NON_NULL) → AuthResolverResponse
Authenticate user account through Google OAuth. This is the 2nd step of OAuth flow.

### passkeyLoginStart(authId: NON_NULL) → PasskeyLoginStartResponse
[INTERNAL] Starts passkey login process.

### passkeyLoginFinish(response: NON_NULL, authId: NON_NULL) → AuthResolverResponse
[INTERNAL] Finish passkey login process.

### createOrganizationFromOnboarding(sessionId: String, survey: OnboardingCustomerSurvey, input: NON_NULL) → CreateOrJoinOrganizationResponse
Creates an organization from onboarding.

### joinOrganizationFromOnboarding(input: NON_NULL) → CreateOrJoinOrganizationResponse
Join an organization from onboarding.

### leaveOrganization(organizationId: NON_NULL) → CreateOrJoinOrganizationResponse
Leave an organization.

### logout(reason: String) → LogoutResponse
Logout the client.

### logoutSession(sessionId: NON_NULL) → LogoutResponse
Logout an individual session with its ID.

### logoutAllSessions(reason: String) → LogoutResponse
Logout all of user's sessions including the active one.

### logoutOtherSessions(reason: String) → LogoutResponse
Logout all of user's sessions excluding the current one.

### attachmentCreate(input: NON_NULL) → AttachmentPayload
Creates a new attachment, or updates existing if the same `url` and `issueId` is used.

### attachmentUpdate(input: NON_NULL, id: NON_NULL) → AttachmentPayload
Updates an existing issue attachment.

### attachmentLinkURL(createAsUser: String, displayIconUrl: String, title: String, url: NON_NULL, issueId: NON_NULL, id: String) → AttachmentPayload
Link any url to an issue.

### attachmentLinkGitLabMR(createAsUser: String, displayIconUrl: String, title: String, issueId: NON_NULL, id: String, url: NON_NULL, projectPathWithNamespace: NON_NULL, number: NON_NULL) → AttachmentPayload
Link an existing GitLab MR to an issue.

### attachmentLinkGitHubIssue(createAsUser: String, displayIconUrl: String, title: String, issueId: NON_NULL, id: String, url: NON_NULL) → AttachmentPayload
Link a GitHub issue to a Linear issue.

### attachmentLinkGitHubPR(createAsUser: String, displayIconUrl: String, title: String, issueId: NON_NULL, id: String, url: NON_NULL, linkKind: GitLinkKind) → AttachmentPayload
Link a GitHub pull request to an issue.

### attachmentLinkZendesk(createAsUser: String, displayIconUrl: String, title: String, ticketId: NON_NULL, issueId: NON_NULL, id: String, url: String) → AttachmentPayload
Link an existing Zendesk ticket to an issue.

### attachmentLinkDiscord(createAsUser: String, displayIconUrl: String, title: String, issueId: NON_NULL, id: String, channelId: NON_NULL, messageId: NON_NULL, url: NON_NULL) → AttachmentPayload
Link an existing Discord message to an issue.

### attachmentSyncToSlack(id: NON_NULL) → AttachmentPayload
Begin syncing the thread for an existing Slack message attachment with a comment thread on its issue.

### attachmentLinkSlack(createAsUser: String, displayIconUrl: String, title: String, issueId: NON_NULL, url: NON_NULL, id: String, syncToCommentThread: Boolean) → AttachmentPayload
Link an existing Slack message to an issue.

### attachmentLinkFront(createAsUser: String, displayIconUrl: String, title: String, conversationId: NON_NULL, issueId: NON_NULL, id: String) → FrontAttachmentPayload
Link an existing Front conversation to an issue.

### attachmentLinkIntercom(createAsUser: String, displayIconUrl: String, title: String, conversationId: NON_NULL, partId: String, id: String, issueId: NON_NULL) → AttachmentPayload
Link an existing Intercom conversation to an issue.

### attachmentLinkJiraIssue(createAsUser: String, displayIconUrl: String, title: String, issueId: NON_NULL, jiraIssueId: NON_NULL, id: String, url: String) → AttachmentPayload
Link an existing Jira issue to an issue.

### attachmentLinkSalesforce(createAsUser: String, displayIconUrl: String, title: String, issueId: NON_NULL, id: String, url: NON_NULL) → AttachmentPayload
Link an existing Salesforce case to an issue.

### attachmentDelete(id: NON_NULL) → DeletePayload
Deletes an issue attachment.

### agentSessionCreateOnComment(input: NON_NULL) → AgentSessionPayload
Creates a new agent session on a rootcomment.

### agentSessionCreateOnIssue(input: NON_NULL) → AgentSessionPayload
Creates a new agent session on an issue.

### agentSessionCreate(pullRequestId: String, input: NON_NULL) → AgentSessionPayload
[Internal] Creates a new agent session on behalf of the current user

### agentSessionUpdateExternalUrl(input: NON_NULL, id: NON_NULL) → AgentSessionPayload
Updates the externalUrl of an agent session, which is an agent-hosted page associated with this session.

### agentSessionUpdate(input: NON_NULL, id: NON_NULL) → AgentSessionPayload
Updates an agent session.

### agentActivityCreate(input: NON_NULL) → AgentActivityPayload
Creates an agent activity.

### agentActivityCreatePrompt(input: NON_NULL) → AgentActivityPayload
[Internal] Creates a prompt agent activity from Linear user input.


## Enums

### AgentActivitySignal
A modifier that provides additional instructions on how the activity should be interpreted.

### AgentActivityType
The type of an agent activity.

### AgentSessionStatus
The status of an agent session.

### AgentSessionType
[DEPRECATED] The type of an agent session.

### AuthenticationSessionType
### ContextViewType
### CustomerStatusType
[DEPRECATED] A type of customer status.

### CustomerVisibilityMode
Mode that controls who can see and set Customers in Slack Asks.

### CyclePeriod
### DateResolutionType
By which resolution is a date defined.

### Day
The day of the week.

### EmailIntakeAddressType
The type of the email address.

### ExternalSyncService
The service that syncs an external entity to Linear.

### FacetPageSource
### FeedSummarySchedule
Cadence to generate feed summary

### FrequencyResolutionType
By which resolution is frequency defined.

### GitAutomationStates
The various states of a pull/merge request.

### GitLinkKind
[Internal] The kind of link between an issue and a pull request.

### GithubOrgType
### IdentityProviderType
The type of identity provider.

### InitiativeStatus
### InitiativeTab
Different tabs available inside an initiative.

### InitiativeUpdateHealthType
The health type when the update is created.

### IntegrationService
Linear supported integration services.

### IssueRelationType
The type of the issue relation.

### IssueSuggestionState
### IssueSuggestionType
### NotificationCategory
The categories of notifications a user can subscribe to.

### NotificationChannel
The delivery channels a user can receive notifications in.

### OAuthClientApprovalStatus
The different requests statuses possible for an OAuth client approval request.

### OrganizationDomainAuthType
What type of auth is the domain used for.

### OrganizationInviteStatus
The different statuses possible for an organization invite.

### PaginationNulls
How to treat NULL values, whether they should appear first or last

### PaginationOrderBy
By which field should the pagination order by

### PaginationSortOrder
Whether to sort in ascending or descending order

### PostType
Type of Post

### ProductIntelligenceScope
[Internal] The scope of product intelligence suggestion data for a team.

### ProjectMilestoneStatus
The status of a project milestone.

### ProjectStatusType
A type of project status.

### ProjectTab
Different tabs available inside a project.

### ProjectUpdateHealthType
The health type when the project update is created.

### ProjectUpdateReminderFrequency
The frequency at which to send project update reminders.

### PullRequestMergeMethod
The method used to merge a pull request.

### PullRequestReviewTool
### PullRequestStatus
The status of a pull request.

### PushSubscriptionType
The different push subscription types.

### ReleaseChannel
Features release channel.

### ReleasePipelineType
A type of release pipeline.

### ReleaseStageType
A type of release stage.

### SLADayCountType
### SemanticSearchResultType
The type of the semantic search result.

### SendStrategy
### SlaStatus
### SlackChannelType
### SummaryGenerationStatus
The generation status of a summary.

### TeamRetirementSubTeamHandling
[Internal] How to handle sub-teams when retiring a parent team.

### TeamRoleType
All possible roles within a team in terms of access to team settings and operations.

### TriageResponsibilityAction
Which action should be taken after an issue is added to triage.

### TriageRuleErrorType
The type of error that occurred during triage rule execution.

### UserContextViewType
### UserFlagType
The types of flags that the user can have.

### UserFlagUpdateOperation
Operations that can be applied to UserFlagType.

### UserRoleType
The different permission roles available to users on an organization.

### UserSettingsThemeDeviceType
Device type for theme

### UserSettingsThemeMode
Theme color mode

### UserSettingsThemePreset
Theme preset options

### ViewPreferencesType
The type of view preferences (either user or organization level preferences).

### ViewType
The client view this custom view is targeting.

### WorkflowTrigger
### WorkflowTriggerType
### WorkflowType

## Input Types

### ActivityCollectionFilter
Activity collection filtering options.

### ActivityFilter
Activity filtering options.

### AgentActivityCreateInput
### AgentActivityCreatePromptInput
[Internal] Input for creating prompt-type agent activities (created by users).

### AgentActivityFilter
Agent activity filtering options.

### AgentActivityPromptCreateInputContent
[Internal] Input for creating prompt-type agent activities (created by users).

### AgentSessionCreateInput
### AgentSessionCreateOnComment
### AgentSessionCreateOnIssue
### AgentSessionExternalUrlInput
Input for an external URL associated with an agent session.

### AgentSessionUpdateExternalUrlInput
### AgentSessionUpdateInput
### AgentSessionUserStateInput
### AirbyteConfigurationInput
### ApproximateNeedCountSort
Customer approximate need count sorting options.

### AssigneeSort
Issue assignee sorting options.

### AttachmentCollectionFilter
Attachment collection filtering options.

### AttachmentCreateInput
### AttachmentFilter
Attachment filtering options.

### AttachmentUpdateInput
### AuditEntryFilter
Audit entry filtering options.

### BooleanComparator
Comparator for booleans.

### CandidateRepository
### CommentCollectionFilter
Comment filtering options.

### CommentCreateInput
### CommentFilter
Comment filtering options.

### CommentUpdateInput
### CompletedAtSort
Issue completion date sorting options.

### ContactCreateInput
### ContactSalesCreateInput
[INTERNAL] Input for sending a message to the Linear Sales team.

### ContentComparator
[Internal] Comparator for content.

### CreateOrganizationInput
### CreatedAtSort
Issue creation date sorting options.

### CustomViewCreateInput
### CustomViewCreatedAtSort
Custom view creation date sorting options.

### CustomViewFilter
Custom view filtering options.

### CustomViewNameSort
Custom view name sorting options.

### CustomViewSharedSort
Custom view shared status sorting options. Ascending order puts shared views last.

### CustomViewSortInput
### CustomViewUpdateInput
### CustomViewUpdatedAtSort
Custom view update date sorting options.

### CustomerCountSort
Issue customer count sorting options.

### CustomerCreateInput
### CustomerCreatedAtSort
Customer creation date sorting options.

### CustomerFilter
Customer filtering options.

### CustomerImportantCountSort
Issue customer important count sorting options.

### CustomerNeedCollectionFilter
Customer needs filtering options.

### CustomerNeedCreateFromAttachmentInput
### CustomerNeedCreateInput
### CustomerNeedFilter
Customer filtering options.

### CustomerNeedUpdateInput
### CustomerRevenueSort
Issue customer revenue sorting options.

### CustomerSort
Issue customer sorting options.

### CustomerSortInput
Customer sorting options.

### CustomerStatusCreateInput
### CustomerStatusFilter
Customer status filtering options.

### CustomerStatusSort
Customer status sorting options.

### CustomerStatusUpdateInput
### CustomerTierCreateInput
### CustomerTierFilter
Customer tier filtering options.

### CustomerTierUpdateInput
### CustomerUpdateInput
### CustomerUpsertInput
### CycleCreateInput
### CycleFilter
Cycle filtering options.

### CyclePeriodComparator
Comparator for period when issue was added to a cycle.

### CycleShiftAllInput
Input for shifting all cycles from a certain cycle onwards by a certain number of days

### CycleSort
Issue cycle sorting options.

### CycleUpdateInput
### DateComparator
Comparator for dates.

### DelegateSort
Issue delegate sorting options.

### DeleteOrganizationInput
### DocumentCreateInput
### DocumentFilter
Document filtering options.

### DocumentUpdateInput
### DueDateSort
Issue due date sorting options.

### EmailIntakeAddressCreateInput
### EmailIntakeAddressUpdateInput
### EmailUnsubscribeInput
### EmailUserAccountAuthChallengeInput
### EmojiCreateInput
### EntityExternalLinkCreateInput
### EntityExternalLinkUpdateInput
### EstimateComparator
Comparator for estimates.

### EstimateSort
Issue estimate sorting options.

### EventTrackingInput
### FavoriteCreateInput
### FavoriteUpdateInput
### FeedItemFilter
Feed item filtering options

### FrontSettingsInput
### GitAutomationStateCreateInput
### GitAutomationStateUpdateInput
### GitAutomationTargetBranchCreateInput
### GitAutomationTargetBranchUpdateInput
### GitHubImportSettingsInput
### GitHubPersonalSettingsInput
### GitHubRepoInput
### GitHubRepoMappingInput
### GitHubSettingsInput
### GitLabSettingsInput
### GongRecordingImportConfigInput
### GongSettingsInput
### GoogleSheetsExportSettings
### GoogleSheetsSettingsInput
### GoogleUserAccountAuthInput
### IDComparator
Comparator for identifiers.

### InheritanceEntityMapping
### InitiativeCollectionFilter
Initiative collection filtering options.

### InitiativeCreateInput
The properties of the initiative to create.

### InitiativeCreatedAtSort
Initiative creation date sorting options.

### InitiativeFilter
Initiative filtering options.

### InitiativeHealthSort
Initiative health sorting options.

### InitiativeHealthUpdatedAtSort
Initiative health update date sorting options.

### InitiativeManualSort
Initiative manual sorting options.

### InitiativeNameSort
Initiative name sorting options.

### InitiativeOwnerSort
Initiative owner sorting options.

### InitiativeRelationCreateInput
### InitiativeRelationUpdateInput
The properties of the initiativeRelation to update.

### InitiativeSortInput
Initiative sorting options.

### InitiativeTargetDateSort
Initiative target date sorting options.

### InitiativeToProjectCreateInput
The properties of the initiativeToProject to create.

### InitiativeToProjectUpdateInput
The properties of the initiativeToProject to update.

### InitiativeUpdateCreateInput
### InitiativeUpdateFilter
Options for filtering initiative updates.

### InitiativeUpdateInput
The properties of the initiative to update.

### InitiativeUpdateUpdateInput
### InitiativeUpdatedAtSort
Initiative update date sorting options.

### IntegrationCustomerDataAttributesRefreshInput
### IntegrationRequestInput
### IntegrationSettingsInput
### IntegrationTemplateCreateInput
### IntegrationUpdateInput
### IntegrationsSettingsCreateInput
### IntegrationsSettingsUpdateInput
### IntercomSettingsInput
### IssueBatchCreateInput
### IssueCollectionFilter
Issue filtering options.

### IssueCreateInput
### IssueFilter
Issue filtering options.

### IssueIDComparator
Comparator for issue identifiers.

### IssueImportUpdateInput
### IssueLabelCollectionFilter
Issue label filtering options.

### IssueLabelCreateInput
### IssueLabelFilter
Issue label filtering options.

### IssueLabelUpdateInput
### IssueReferenceInput
A reference to an issue found during release creation.

### IssueRelationCreateInput
### IssueRelationUpdateInput
### IssueSortInput
Issue sorting options.

### IssueSuggestionCollectionFilter
IssueSuggestion collection filtering options.

### IssueSuggestionFilter
IssueSuggestion filtering options.

### IssueToReleaseCreateInput
[ALPHA] The properties of the issueToRelease to create.

### IssueUpdateInput
### JiraConfigurationInput
### JiraFetchProjectStatusesInput
### JiraLinearMappingInput
### JiraPersonalSettingsInput
### JiraProjectDataInput
### JiraSettingsInput
### JiraUpdateInput
### JoinOrganizationInput
### LabelGroupSort
Issue label-group sorting options.

### LabelSort
Issue label sorting options.

### LaunchDarklySettingsInput
### LinkCountSort
[ALPHA] Issue link count sorting options.

### ManualSort
Issue manual sorting options.

### MicrosoftTeamsSettingsInput
### MilestoneSort
Issue project milestone options.

### NameSort
Customer name sorting options.

### NotificationCategoryPreferencesInput
### NotificationDeliveryPreferencesChannelInput
### NotificationDeliveryPreferencesDayInput
### NotificationDeliveryPreferencesInput
### NotificationDeliveryPreferencesScheduleInput
### NotificationEntityInput
Describes the type and id of the entity to target for notifications.

### NotificationFilter
Notification filtering options.

### NotificationSubscriptionCreateInput
### NotificationSubscriptionUpdateInput
### NotificationUpdateInput
### NotionSettingsInput
### NullableCommentFilter
Comment filtering options.

### NullableCustomerFilter
Customer filtering options.

### NullableCycleFilter
Cycle filtering options.

### NullableDateComparator
Comparator for optional dates.

### NullableDocumentContentFilter
Document content filtering options.

### NullableDurationComparator
Nullable comparator for optional durations.

### NullableIssueFilter
Issue filtering options.

### NullableNumberComparator
Comparator for optional numbers.

### NullableProjectFilter
Project filtering options.

### NullableProjectMilestoneFilter
Project milestone filtering options.

### NullableProjectUpdateFilter
Nullable project update filtering options.

### NullableStringComparator
Comparator for optional strings.

### NullableTeamFilter
Team filtering options.

### NullableTemplateFilter
Template filtering options.

### NullableTimelessDateComparator
Comparator for optional timeless dates.

### NullableUserFilter
User filtering options.

### NumberComparator
Comparator for numbers.

### OnboardingCustomerSurvey
### OpsgenieInput
### OrganizationDomainCreateInput
### OrganizationDomainUpdateInput
### OrganizationDomainVerificationInput
### OrganizationInviteCreateInput
### OrganizationInviteUpdateInput
### OrganizationIpRestrictionInput
[INTERNAL] Organization IP restriction configuration.

### OrganizationSecuritySettingsInput
### OrganizationStartTrialInput
### OrganizationUpdateInput
### OwnerSort
Customer owner sorting options.

### PagerDutyInput
### PartialNotificationChannelPreferencesInput
### PrioritySort
Issue priority sorting options.

### ProjectCollectionFilter
Project filtering options.

### ProjectCreateInput
### ProjectCreatedAtSort
Project creation date sorting options.

### ProjectFilter
Project filtering options.

### ProjectHealthSort
Project health sorting options.

### ProjectLabelCollectionFilter
Project label filtering options.

### ProjectLabelCreateInput
### ProjectLabelFilter
Project label filtering options.

### ProjectLabelUpdateInput
### ProjectLeadSort
Project lead sorting options.

### ProjectManualSort
Project manual order sorting options.

### ProjectMilestoneCollectionFilter
Milestone collection filtering options.

### ProjectMilestoneCreateInput
### ProjectMilestoneFilter
Project milestone filtering options.

### ProjectMilestoneMoveInput
### ProjectMilestoneMoveIssueToTeamInput
[Internal] Used for ProjectMilestoneMoveInput to describe a mapping between an issue and its team.

### ProjectMilestoneMoveProjectTeamsInput
[Internal] Used for ProjectMilestoneMoveInput to describe a snapshot of a project and its team ids

### ProjectMilestoneUpdateInput
### ProjectNameSort
Project name sorting options.

### ProjectPrioritySort
Project priority sorting options.

### ProjectRelationCreateInput
### ProjectRelationUpdateInput
### ProjectSort
Issue project sorting options.

### ProjectSortInput
Project sorting options.

### ProjectStatusCreateInput
### ProjectStatusFilter
Project status filtering options.

### ProjectStatusSort
Project status sorting options.

### ProjectStatusUpdateInput
### ProjectUpdateCreateInput
### ProjectUpdateFilter
Options for filtering project updates.

### ProjectUpdateInput
### ProjectUpdateUpdateInput
### ProjectUpdatedAtSort
Project update date sorting options.

### ProjectUpdatesCollectionFilter
Collection filtering options for filtering projects by project updates.

### ProjectUpdatesFilter
Options for filtering projects by project updates.

### PullRequestReferenceInput
Input for referencing a pull request by repository and number.

### PushSubscriptionCreateInput
### ReactionCollectionFilter
Reaction filtering options.

### ReactionCreateInput
### ReactionFilter
Reaction filtering options.

### RelationExistsComparator
Comparator for relation existence.

### ReleaseCollectionFilter
[ALPHA] Release collection filtering options.

### ReleaseCompleteInput
### ReleaseCompleteInputBase
### ReleaseCreateInput
The input for creating a release.

### ReleaseDebugSinkInput
Debug sink for release creation diagnostics.

### ReleaseFilter
[ALPHA] Release filtering options.

### ReleasePipelineCreateInput
### ReleasePipelineFilter
[ALPHA] Release pipeline filtering options.

### ReleasePipelineUpdateInput
### ReleaseStageCreateInput
### ReleaseStageFilter
[ALPHA] Release stage filtering options.

### ReleaseStageTypeComparator
[ALPHA] Comparator for release stage type.

### ReleaseStageUpdateInput
### ReleaseSyncInput
The release data to sync.

### ReleaseSyncInputBase
Base release sync data without pipeline specification.

### ReleaseUpdateByPipelineInput
Input for updating a release by pipeline.

### ReleaseUpdateByPipelineInputBase
### ReleaseUpdateInput
### RepositoryDataInput
Information about the source repository.

### RevenueSort
Customer revenue sorting options.

### RoadmapCollectionFilter
Roadmap collection filtering options.

### RoadmapCreateInput
### RoadmapFilter
Roadmap filtering options.

### RoadmapToProjectCreateInput
### RoadmapToProjectUpdateInput
### RoadmapUpdateInput
### RootIssueSort
Issue root-issue sorting options.

### SalesforceMetadataIntegrationComparator
[INTERNAL] Comparator for Salesforce metadata.

### SalesforceSettingsInput
### SemanticSearchFilters
Filters for semantic search results.

### SentrySettingsInput
### SizeSort
Customer size sorting options.

### SlaStatusComparator
Comparator for sla status.

### SlaStatusSort
Issue SLA status sorting options.

### SlackAsksSettingsInput
### SlackAsksTeamSettingsInput
### SlackChannelNameMappingInput
### SlackPostSettingsInput
### SlackSettingsInput
### SourceMetadataComparator
Comparator for issue source type.

### SourceTypeComparator
Comparator for `sourceType` field.

### StartDateSort
Project start date sorting options.

### StringArrayComparator
Comparator for strings.

### StringComparator
Comparator for strings.

### StringItemComparator
Comparator for strings in arrays.

### SubTypeComparator
Comparator for source type.

### TargetDateSort
Project target date sorting options.

### TeamCollectionFilter
Team collection filtering options.

### TeamCreateInput
### TeamFilter
Team filtering options.

### TeamMembershipCreateInput
### TeamMembershipUpdateInput
### TeamSecuritySettingsInput
### TeamSort
Issue team sorting options.

### TeamUpdateInput
### TemplateCreateInput
### TemplateUpdateInput
### TierSort
Customer tier sorting options.

### TimeInStatusSort
Issue time in status sorting options.

### TimeScheduleCreateInput
### TimeScheduleEntryInput
### TimeScheduleUpdateInput
### TitleSort
Issue title sorting options.

### TokenUserAccountAuthInput
### TriageResponsibilityCreateInput
### TriageResponsibilityManualSelectionInput
Manual triage responsibility using a set of users.

### TriageResponsibilityUpdateInput
### UpdatedAtSort
Issue update date sorting options.

### UserCollectionFilter
User filtering options.

### UserDisplayNameSort
User display name sorting options.

### UserFilter
User filtering options.

### UserNameSort
User name sorting options.

### UserSettingsUpdateInput
### UserSortInput
User sorting options.

### UserUpdateInput
### ViewPreferencesCreateInput
### ViewPreferencesUpdateInput
### WebhookCreateInput
### WebhookUpdateInput
### WorkflowStateCreateInput
### WorkflowStateFilter
Workflow state filtering options.

### WorkflowStateSort
Issue workflow state sorting options.

### WorkflowStateUpdateInput
### ZendeskSettingsInput

## Object Types

### ActorBot
A bot actor is an actor that is not a user, but an application or integration.

### AgentActivity
An activity within an agent context.

### AgentActivityActionContent
Content for an action activity (tool call or action).

### AgentActivityConnection
### AgentActivityEdge
### AgentActivityElicitationContent
Content for an elicitation activity.

### AgentActivityErrorContent
Content for an error activity.

### AgentActivityPayload
### AgentActivityPromptContent
Content for a prompt activity.

### AgentActivityResponseContent
Content for a response activity.

### AgentActivityThoughtContent
Content for a thought activity.

### AgentSession
A session for agent activities and state management.

### AgentSessionConnection
### AgentSessionEdge
### AgentSessionExternalLink
An external link associated with an agent session.

### AgentSessionPayload
### AgentSessionToPullRequest
Join table between agent sessions and pull requests.

### AgentSessionToPullRequestConnection
### AgentSessionToPullRequestEdge
### AiPromptRules
AI prompt rules for a team.

### Application
Public information of the OAuth application.

### ArchiveResponse
Contains requested archived model objects.

### AsksChannelConnectPayload
### Attachment
Issue attachment (e.g. support ticket, pull request).

### AttachmentConnection
### AttachmentEdge
### AttachmentPayload
### AttachmentSourcesPayload
### AuditEntry
Workspace audit log entry object.

### AuditEntryConnection
### AuditEntryEdge
### AuditEntryType
### AuthIdentityProvider
An identity provider.

### AuthOrganization
An organization. Organizations are root-level objects that contain users and teams.

### AuthResolverResponse
### AuthUser
A user that has access to the the resources of an organization.

### AuthenticationSessionResponse
Authentication session information.

### CodingAgentSandboxPayload
[Internal] Coding agent sandbox details for an agent session.

### Comment
A comment associated with an issue.

### CommentConnection
### CommentEdge
### CommentPayload
### ContactPayload
### CreateCsvExportReportPayload
### CreateOrJoinOrganizationResponse
### CustomView
A custom view that has been saved by a user.

### CustomViewConnection
### CustomViewEdge
### CustomViewHasSubscribersPayload
### CustomViewNotificationSubscription
A custom view notification subscription.

### CustomViewPayload
### CustomViewSuggestionPayload
### Customer
A customer whose needs will be tied to issues or projects.

### CustomerConnection
### CustomerEdge
### CustomerNeed
A customer need, expressed through a reference to an issue, project, or comment.

### CustomerNeedArchivePayload
A generic payload return from entity archive mutations.

### CustomerNeedConnection
### CustomerNeedEdge
### CustomerNeedNotification
A customer need related notification.

### CustomerNeedPayload
### CustomerNeedUpdatePayload
### CustomerNotification
A customer related notification.

### CustomerNotificationSubscription
A customer notification subscription.

### CustomerPayload
### CustomerStatus
A customer status.

### CustomerStatusConnection
### CustomerStatusEdge
### CustomerStatusPayload
### CustomerTier
A customer tier.

### CustomerTierConnection
### CustomerTierEdge
### CustomerTierPayload
### Cycle
A set of issues to be resolved in a specified amount of time.

### CycleArchivePayload
A generic payload return from entity archive mutations.

### CycleConnection
### CycleEdge
### CycleNotificationSubscription
A cycle notification subscription.

### CyclePayload
### Dashboard
[Internal] A dashboard, usually a collection of widgets to display several insights at once.

### DeletePayload
A generic payload return from entity deletion mutations.

### Document
A document that can be attached to different entities.

### DocumentArchivePayload
A generic payload return from entity archive mutations.

### DocumentConnection
### DocumentContent
A document content for a project.

### DocumentContentHistoryPayload
### DocumentContentHistoryType
### DocumentEdge
### DocumentNotification
A document related notification.

### DocumentPayload
### DocumentSearchPayload
### DocumentSearchResult
### DocumentSearchResultEdge
### Draft
A general purpose draft. Used for comments, project updates, etc.

### DraftConnection
### DraftEdge
### EmailIntakeAddress
An email address that can be used for submitting issues.

### EmailIntakeAddressPayload
### EmailUnsubscribePayload
### EmailUserAccountAuthChallengeResponse
### Emoji
A custom emoji.

### EmojiConnection
### EmojiEdge
### EmojiPayload
### EntityExternalLink
An external link for an entity like initiative, etc...

### EntityExternalLinkConnection
### EntityExternalLinkEdge
### EntityExternalLinkPayload
### EventTrackingPayload
### ExternalEntityInfo
Information about an external entity.

### ExternalEntityInfoGithubMetadata
Metadata about the external GitHub entity.

### ExternalEntityInfoJiraMetadata
Metadata about the external Jira entity.

### ExternalEntitySlackMetadata
Metadata about the external Slack entity.

### ExternalUser
An external authenticated (e.g., through Slack) user which doesn't have a Linear account, but can create and update entities in Linear from the external system that authenticated them.

### ExternalUserConnection
### ExternalUserEdge
### Facet
A facet. Facets are joins between entities. A facet can tie a custom view to a project, or a a project to a roadmap for example.

### FacetConnection
### FacetEdge
### Favorite
User favorites presented in the sidebar.

### FavoriteConnection
### FavoriteEdge
### FavoritePayload
### FeedItem
[Internal] An item in a users feed.

### FeedItemConnection
### FeedItemEdge
### FetchDataPayload
### FileUploadDeletePayload
### FrontAttachmentPayload
### GitAutomationState
A trigger that updates the issue status according to Git automations.

### GitAutomationStateConnection
### GitAutomationStateEdge
### GitAutomationStatePayload
### GitAutomationTargetBranch
A Git target branch for which there are automations (GitAutomationState).

### GitAutomationTargetBranchPayload
### GitHubCommitIntegrationPayload
### GitHubEnterpriseServerInstallVerificationPayload
### GitHubEnterpriseServerPayload
### GitLabIntegrationCreatePayload
### GitLabTestConnectionPayload
### IdentityProvider
An identity provider.

### ImageUploadFromUrlPayload
### Initiative
An initiative to group projects.

### InitiativeArchivePayload
A generic payload return from entity archive mutations.

### InitiativeConnection
### InitiativeEdge
### InitiativeHistory
A initiative history containing relevant change events.

### InitiativeHistoryConnection
### InitiativeHistoryEdge
### InitiativeNotification
An initiative related notification.

### InitiativeNotificationSubscription
An initiative notification subscription.

### InitiativePayload
The payload returned by the initiative mutations.

### InitiativeRelation
A relation representing the dependency between two initiatives.

### InitiativeRelationConnection
### InitiativeRelationEdge
### InitiativeRelationPayload
### InitiativeToProject
Join table between projects and initiatives.

### InitiativeToProjectConnection
### InitiativeToProjectEdge
### InitiativeToProjectPayload
The result of a initiativeToProject mutation.

### InitiativeUpdate
An initiative update.

### InitiativeUpdateArchivePayload
A generic payload return from entity archive mutations.

### InitiativeUpdateConnection
### InitiativeUpdateEdge
### InitiativeUpdatePayload
### InitiativeUpdateReminderPayload
### Integration
An integration with an external service.

### IntegrationConnection
### IntegrationEdge
### IntegrationHasScopesPayload
### IntegrationPayload
### IntegrationRequestPayload
### IntegrationSlackWorkspaceNamePayload
### IntegrationTemplate
Join table between templates and integrations.

### IntegrationTemplateConnection
### IntegrationTemplateEdge
### IntegrationTemplatePayload
### IntegrationsSettings
The configuration of all integrations for different entities.

### IntegrationsSettingsPayload
### Issue
An issue.

### IssueArchivePayload
A generic payload return from entity archive mutations.

### IssueBatchPayload
### IssueConnection
### IssueDraft
[Internal] A draft issue.

### IssueDraftConnection
### IssueDraftEdge
### IssueEdge
### IssueFilterSuggestionPayload
### IssueHistory
A record of changes to an issue.

### IssueHistoryConnection
### IssueHistoryEdge
### IssueHistoryTriageRuleError
An error that occurred during triage rule execution.

### IssueHistoryTriageRuleMetadata
Metadata about a triage rule that made changes to an issue.

### IssueImport
An import job for data from an external service.

### IssueImportCheckPayload
### IssueImportDeletePayload
### IssueImportJqlCheckPayload
Whether a custom JQL query is valid or not

### IssueImportPayload
### IssueImportSyncCheckPayload
Whether an issue import can be synced at the end of an import or not

### IssueLabel
Labels that can be associated with issues.

### IssueLabelConnection
### IssueLabelEdge
### IssueLabelPayload
### IssueNotification
An issue related notification.

### IssuePayload
### IssuePriorityValue
### IssueRelation
A relation between two issues.

### IssueRelationConnection
### IssueRelationEdge
### IssueRelationHistoryPayload
Issue relation history's payload.

### IssueRelationPayload
### IssueSearchPayload
### IssueSearchResult
### IssueSearchResultEdge
### IssueSharedAccess
### IssueStateSpan
A continuous period of time during which an issue remained in a specific workflow state.

### IssueStateSpanConnection
### IssueStateSpanEdge
### IssueSuggestion
### IssueSuggestionConnection
### IssueSuggestionEdge
### IssueSuggestionMetadata
### IssueTitleSuggestionFromCustomerRequestPayload
### IssueToRelease
[Internal] Join table between issues and releases.

### IssueToReleaseConnection
### IssueToReleaseEdge
### IssueToReleasePayload
[ALPHA] The result of an issueToRelease mutation.

### JiraFetchProjectStatusesPayload
### LabelNotificationSubscription
A label notification subscription.

### LogoutResponse
### Mutation
### NotificationArchivePayload
A generic payload return from entity archive mutations.

### NotificationBatchActionPayload
### NotificationCategoryPreferences
A user's notification category preferences.

### NotificationChannelPreferences
A user's notification channel preferences, indicating if a channel is enabled or not

### NotificationConnection
### NotificationDeliveryPreferences
A user's notification delivery preferences.

### NotificationDeliveryPreferencesChannel
A user's notification delivery preferences.

### NotificationDeliveryPreferencesDay
A user's notification delivery schedule for a particular day.

### NotificationDeliveryPreferencesSchedule
A user's notification delivery schedule for a particular day.

### NotificationEdge
### NotificationPayload
### NotificationSubscriptionConnection
### NotificationSubscriptionEdge
### NotificationSubscriptionPayload
### OauthClientApproval
Request to install OAuth clients on organizations and the response to the request.

### OauthClientApprovalNotification
An oauth client approval related notification.

### Organization
An organization. Organizations are root-level objects that contain user accounts and teams.

### OrganizationAcceptedOrExpiredInviteDetailsPayload
### OrganizationCancelDeletePayload
### OrganizationDeletePayload
### OrganizationDomain
Defines the use of a domain by an organization.

### OrganizationDomainClaimPayload
[INTERNAL] Domain claim request response.

### OrganizationDomainPayload
[INTERNAL] Organization domain operation response.

### OrganizationDomainSimplePayload
[INTERNAL] Organization domain operation response.

### OrganizationExistsPayload
### OrganizationInvite
An invitation to the organization that has been sent via email.

### OrganizationInviteConnection
### OrganizationInviteEdge
### OrganizationInviteFullDetailsPayload
### OrganizationInvitePayload
### OrganizationIpRestriction
### OrganizationMeta
### OrganizationPayload
### OrganizationStartTrialPayload
### PageInfo
### PaidSubscription
The paid subscription of an organization.

### PasskeyLoginStartResponse
### Post
[Internal] A generic post.

### PostNotification
A post related notification.

### Project
A project.

### ProjectArchivePayload
A generic payload return from entity archive mutations.

### ProjectAttachment
Project attachment

### ProjectAttachmentConnection
### ProjectAttachmentEdge
### ProjectConnection
### ProjectEdge
### ProjectFilterSuggestionPayload
### ProjectHistory
An history associated with a project.

### ProjectHistoryConnection
### ProjectHistoryEdge
### ProjectLabel
Labels that can be associated with projects.

### ProjectLabelConnection
### ProjectLabelEdge
### ProjectLabelPayload
### ProjectMilestone
A milestone for a project.

### ProjectMilestoneConnection
### ProjectMilestoneEdge
### ProjectMilestoneMoveIssueToTeam
### ProjectMilestoneMovePayload
### ProjectMilestoneMoveProjectTeams
### ProjectMilestonePayload
### ProjectNotification
A project related notification.

### ProjectNotificationSubscription
A project notification subscription.

### ProjectPayload
### ProjectRelation
A relation between two projects.

### ProjectRelationConnection
### ProjectRelationEdge
### ProjectRelationPayload
### ProjectSearchPayload
### ProjectSearchResult
### ProjectSearchResultEdge
### ProjectStatus
A project status.

### ProjectStatusArchivePayload
A generic payload return from entity archive mutations.

### ProjectStatusConnection
### ProjectStatusCountPayload
### ProjectStatusEdge
### ProjectStatusPayload
### ProjectUpdate
An update associated with a project.

### ProjectUpdateArchivePayload
A generic payload return from entity archive mutations.

### ProjectUpdateConnection
### ProjectUpdateEdge
### ProjectUpdatePayload
### ProjectUpdateReminderPayload
### PullRequest
[Internal] A pull request in a version control system.

### PullRequestCheck
[ALPHA] A pull request check.

### PullRequestCommit
[ALPHA] A pull request commit.

### PullRequestMergeSettings
[Internal] Merge settings for a pull request

### PullRequestNotification
A pull request related notification.

### PushSubscription
A user's web or mobile push notification subscription.

### PushSubscriptionPayload
### PushSubscriptionTestPayload
### Query
### RateLimitPayload
### RateLimitResultPayload
### Reaction
A reaction associated with a comment or a project update.

### ReactionPayload
### Release
[Internal] A release.

### ReleaseArchivePayload
A generic payload return from entity archive mutations.

### ReleaseConnection
### ReleaseEdge
### ReleasePayload
### ReleasePipeline
[Internal] A release pipeline.

### ReleasePipelineArchivePayload
A generic payload return from entity archive mutations.

### ReleasePipelineConnection
### ReleasePipelineEdge
### ReleasePipelinePayload
### ReleaseStage
[Internal] A release stage.

### ReleaseStageArchivePayload
A generic payload return from entity archive mutations.

### ReleaseStageConnection
### ReleaseStageEdge
### ReleaseStagePayload
### RepositorySuggestion
### RepositorySuggestionsPayload
### Roadmap
[Deprecated] A roadmap for projects.

### RoadmapArchivePayload
A generic payload return from entity archive mutations.

### RoadmapConnection
### RoadmapEdge
### RoadmapPayload
### RoadmapToProject
[Deprecated] Join table between projects and roadmaps.

### RoadmapToProjectConnection
### RoadmapToProjectEdge
### RoadmapToProjectPayload
### SemanticSearchPayload
Payload returned by semantic search.

### SemanticSearchResult
A semantic search result reference.

### SesDomainIdentity
SES domain identity used for sending emails from a custom domain.

### SesDomainIdentityDnsRecord
A DNS record for a SES domain identity.

### SlackAsksTeamSettings
Tuple for mapping Slack channel IDs to names.

### SlackChannelConnectPayload
### SlackChannelNameMapping
Object for mapping Slack channel IDs to names and other settings.

### SsoUrlFromEmailResponse
### SuccessPayload
### Summary
An AI-generated summary.

### SyncedExternalThread
A comment thread that is synced with an external source.

### Team
An organizational unit that contains issues.

### TeamArchivePayload
A generic payload return from entity archive mutations.

### TeamConnection
### TeamEdge
### TeamMembership
Defines the membership of a user to a team.

### TeamMembershipConnection
### TeamMembershipEdge
### TeamMembershipPayload
### TeamNotificationSubscription
A team notification subscription.

### TeamPayload
### Template
A template object used for creating entities faster.

### TemplateConnection
### TemplateEdge
### TemplatePayload
### TimeSchedule
A time schedule.

### TimeScheduleConnection
### TimeScheduleEdge
### TimeScheduleEntry
### TimeSchedulePayload
### TriageResponsibility
A team's triage responsibility.

### TriageResponsibilityConnection
### TriageResponsibilityEdge
### TriageResponsibilityManualSelection
### TriageResponsibilityPayload
### UploadFile
Object representing Google Cloud upload policy, plus additional data.

### UploadFileHeader
### UploadPayload
### User
A user that has access to the the resources of an organization.

### UserAdminPayload
### UserConnection
### UserEdge
### UserNotificationSubscription
A user notification subscription.

### UserPayload
### UserSettings
The settings of a user as a JSON object.

### UserSettingsCustomSidebarTheme
### UserSettingsCustomTheme
### UserSettingsFlagPayload
### UserSettingsFlagsResetPayload
### UserSettingsPayload
### UserSettingsTheme
### ViewPreferences
View preferences.

### ViewPreferencesPayload
### ViewPreferencesProjectLabelGroupColumn
A label group column configuration for the project list view.

### ViewPreferencesValues
### Webhook
A webhook used to send HTTP notifications over data updates.

### WebhookConnection
### WebhookEdge
### WebhookFailureEvent
Entity representing a webhook execution failure.

### WebhookPayload
### WebhookRotateSecretPayload
### WelcomeMessage
A welcome message for new users joining the workspace.

### WelcomeMessageNotification
A welcome message related notification.

### WorkflowDefinition
### WorkflowState
A state in a team workflow.

### WorkflowStateArchivePayload
A generic payload return from entity archive mutations.

### WorkflowStateConnection
### WorkflowStateEdge
### WorkflowStatePayload

---


# Linear GraphQL API — Object Type Details

## Attachment
Issue attachment (e.g. support ticket, pull request).

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| title | String | Content for the title line in the Linear attachment widget. |
| subtitle | String | Content for the subtitle line in the Linear attachment widget. |
| url | String | Location of the attachment which is also used as an identifier. |
| creator | User | The creator of the attachment. |
| externalUserCreator | ExternalUser | The non-Linear user who created the attachment. |
| metadata | JSONObject | Custom metadata related to the attachment. |
| source | JSONObject | Information about the source which created the attachment. |
| sourceType | String | An accessor helper to source.type, defines the source type of the attachment. |
| groupBySource | Boolean | Indicates if attachments for the same source application should be grouped in the Linear UI. |
| originalIssue | Issue | The issue this attachment was originally created on. Will be undefined if the attachment hasn't been moved. |
| issue | Issue | The issue this attachment belongs to. |
| bodyData | String | The body data of the attachment, if any. |

## AttachmentConnection
| Field | Type | Description |
|-------|------|-------------|
| edges | NON_NULL |  |
| nodes | NON_NULL |  |
| pageInfo | PageInfo |  |

## AttachmentPayload
| Field | Type | Description |
|-------|------|-------------|
| lastSyncId | Float | The identifier of the last sync operation. |
| attachment | Attachment | The issue attachment that was created. |
| success | Boolean | Whether the operation was successful. |

## Comment
A comment associated with an issue.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| body | String | The comment content in markdown format. |
| issue | Issue | The issue that the comment is associated with. |
| issueId | String | The ID of the issue that the comment is associated with. |
| documentContent | DocumentContent | The document content that the comment is associated with. |
| documentContentId | String | The ID of the document content that the comment is associated with. |
| projectUpdate | ProjectUpdate | The project update that the comment is associated with. |
| projectUpdateId | String | The ID of the project update that the comment is associated with. |
| initiativeUpdate | InitiativeUpdate | The initiative update that the comment is associated with. |
| initiativeUpdateId | String | The ID of the initiative update that the comment is associated with. |
| post | Post | The post that the comment is associated with. |
| parent | Comment | The parent comment under which the current comment is nested. |
| parentId | String | The ID of the parent comment under which the current comment is nested. |
| resolvingUser | User | The user that resolved the thread. |
| resolvedAt | DateTime | The time the resolvingUser resolved the thread. |
| resolvingComment | Comment | The comment that resolved the thread. |
| resolvingCommentId | String | The ID of the comment that resolved the thread. |
| user | User | The user who wrote the comment. |
| externalUser | ExternalUser | The external user who wrote the comment. |
| editedAt | DateTime | The time user edited the comment. |
| bodyData | String | [Internal] The comment content as a Prosemirror document. |
| quotedText | String | The text that this comment references. Only defined for inline comments. |
| reactionData | JSONObject | Emoji reaction summary, grouped by emoji type. |
| threadSummary | JSONObject | [Internal] A generated summary of the comment thread. |
| isArtificialAgentSessionRoot | Boolean | [Internal] Whether the comment is an artificial placeholder for an agent session thread created without a comment mention. |
| url | String | Comment's URL. |
| children | CommentConnection | The children of the comment. |
| agentSession | AgentSession | Agent session associated with this comment. |
| agentSessions | AgentSessionConnection | [Internal] Agent sessions associated with this comment. |
| spawnedAgentSessions | AgentSessionConnection | [Internal] Agent sessions spawned from this comment. |
| createdIssues | IssueConnection | Issues created from this comment. |
| botActor | ActorBot | The bot that created the comment. |
| onBehalfOf | User | [Internal] The user on whose behalf the comment was created, e.g. when the Linear assistant creates a comment for a user. |
| externalThread | SyncedExternalThread | The external thread that the comment is synced with. |
| hideInLinear | Boolean | [Internal] Whether the comment should be hidden from Linear clients. This is typically used for bot comments that provide redundant information (e.g., Slack Asks confirmation messages). |
| reactions | NON_NULL | Reactions associated with the comment. |
| syncedWith | LIST | The external services the comment is synced with. |

## CommentConnection
| Field | Type | Description |
|-------|------|-------------|
| edges | NON_NULL |  |
| nodes | NON_NULL |  |
| pageInfo | PageInfo |  |

## CommentPayload
| Field | Type | Description |
|-------|------|-------------|
| lastSyncId | Float | The identifier of the last sync operation. |
| comment | Comment | The comment that was created or updated. |
| success | Boolean | Whether the operation was successful. |

## CustomView
A custom view that has been saved by a user.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| name | String | The name of the custom view. |
| description | String | The description of the custom view. |
| icon | String | The icon of the custom view. |
| color | String | The color of the icon of the custom view. |
| organization | Organization | The organization of the custom view. |
| creator | User | The user who created the custom view. |
| owner | User | The user who owns the custom view. |
| updatedBy | User | The user who last updated the custom view. |
| filterData | JSONObject | The filter applied to issues in the custom view. |
| projectFilterData | JSONObject | The filter applied to projects in the custom view. |
| initiativeFilterData | JSONObject | The filter applied to initiatives in the custom view. |
| feedItemFilterData | JSONObject | The filter applied to feed items in the custom view. |
| shared | Boolean | Whether the custom view is shared with everyone in the organization. |
| slugId | String | The custom view's unique URL slug. |
| modelName | String | The model name of the custom view. |
| facet | Facet | [INTERNAL] The facet associated with the custom view. |
| team | Team | The team associated with the custom view. |
| projects | ProjectConnection | Projects associated with the custom view. |
| issues | IssueConnection | Issues associated with the custom view. |
| updates | FeedItemConnection | Feed items associated with the custom view. |
| userViewPreferences | ViewPreferences | The current users view preferences for this custom view. |
| organizationViewPreferences | ViewPreferences | The organizations default view preferences for this custom view. |
| viewPreferencesValues | ViewPreferencesValues | The calculated view preferences values for this custom view. |
| initiatives | InitiativeConnection | Initiatives associated with the custom view. |

## CustomViewConnection
| Field | Type | Description |
|-------|------|-------------|
| edges | NON_NULL |  |
| nodes | NON_NULL |  |
| pageInfo | PageInfo |  |

## Cycle
A set of issues to be resolved in a specified amount of time.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| number | Float | The number of the cycle. |
| name | String | The custom name of the cycle. |
| description | String | The cycle's description. |
| startsAt | DateTime | The start time of the cycle. |
| endsAt | DateTime | The end time of the cycle. |
| completedAt | DateTime | The completion time of the cycle. If null, the cycle hasn't been completed. |
| autoArchivedAt | DateTime | The time at which the cycle was automatically archived by the auto pruning process. |
| issueCountHistory | NON_NULL | The total number of issues in the cycle after each day. |
| completedIssueCountHistory | NON_NULL | The number of completed issues in the cycle after each day. |
| scopeHistory | NON_NULL | The total number of estimation points after each day. |
| completedScopeHistory | NON_NULL | The number of completed estimation points after each day. |
| inProgressScopeHistory | NON_NULL | The number of in progress estimation points after each day. |
| team | Team | The team that the cycle is associated with. |
| progressHistory | JSONObject | [Internal] The progress history of the cycle. |
| currentProgress | JSONObject | [Internal] The current progress of the cycle. |
| inheritedFrom | Cycle | The cycle inherited from. |
| isActive | Boolean | Whether the cycle is currently active. |
| isFuture | Boolean | Whether the cycle is in the future. |
| isPast | Boolean | Whether the cycle is in the past. |
| issues | IssueConnection | Issues associated with the cycle. |
| uncompletedIssuesUponClose | IssueConnection | Issues that weren't completed when the cycle was closed. |
| progress | Float | The overall progress of the cycle. This is the (completed estimate points + 0.25 * in progress estimate points) / total estimate points. |
| isNext | Boolean | Whether the cycle is the next cycle for the team. |
| isPrevious | Boolean | Whether the cycle is the previous cycle for the team. |
| documents | DocumentConnection | [Internal] Documents associated with the cycle. |
| links | EntityExternalLinkConnection | [Internal] Links associated with the cycle. |

## CycleConnection
| Field | Type | Description |
|-------|------|-------------|
| edges | NON_NULL |  |
| nodes | NON_NULL |  |
| pageInfo | PageInfo |  |

## CyclePayload
| Field | Type | Description |
|-------|------|-------------|
| lastSyncId | Float | The identifier of the last sync operation. |
| cycle | Cycle | The Cycle that was created or updated. |
| success | Boolean | Whether the operation was successful. |

## Document
A document that can be attached to different entities.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| title | String | The document title. |
| icon | String | The icon of the document. |
| color | String | The color of the icon. |
| creator | User | The user who created the document. |
| updatedBy | User | The user who last updated the document. |
| project | Project | The project that the document is associated with. |
| initiative | Initiative | The initiative that the document is associated with. |
| team | Team | [Internal] The team that the document is associated with. |
| issue | Issue | The issue that the document is associated with. |
| release | Release | [Internal] The release that the document is associated with. |
| cycle | Cycle | [Internal] The cycle that the document is associated with. |
| slugId | String | The document's unique URL slug. |
| lastAppliedTemplate | Template | The last template that was applied to this document. |
| hiddenAt | DateTime | The time at which the document was hidden. Null if the entity has not been hidden. |
| trashed | Boolean | A flag that indicates whether the document is in the trash bin. |
| sortOrder | Float | The order of the item in the resources list. |
| comments | CommentConnection | Comments associated with the document. |
| content | String | The documents content in markdown format. |
| contentState | String | [Internal] The documents content as YJS state. |
| documentContentId | String | The ID of the document content associated with the document. |
| url | String | The canonical url for the document. |

## DocumentConnection
| Field | Type | Description |
|-------|------|-------------|
| edges | NON_NULL |  |
| nodes | NON_NULL |  |
| pageInfo | PageInfo |  |

## DocumentPayload
| Field | Type | Description |
|-------|------|-------------|
| lastSyncId | Float | The identifier of the last sync operation. |
| document | Document | The document that was created or updated. |
| success | Boolean | Whether the operation was successful. |

## Emoji
A custom emoji.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| name | String | The emoji's name. |
| url | String | The emoji image URL. |
| source | String | The source of the emoji. |
| creator | User | The user who created the emoji. |
| organization | Organization | The organization that the emoji belongs to. |

## EmojiConnection
| Field | Type | Description |
|-------|------|-------------|
| edges | NON_NULL |  |
| nodes | NON_NULL |  |
| pageInfo | PageInfo |  |

## Favorite
User favorites presented in the sidebar.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| type | String | The type of the favorite. |
| parent | Favorite | The parent folder of the favorite. |
| folderName | String | The name of the folder. Only applies to favorites of type folder. |
| projectTab | ProjectTab | The targeted tab of the project. |
| predefinedViewType | String | The type of favorited predefined view. |
| initiativeTab | InitiativeTab | The targeted tab of the initiative. |
| owner | User | The owner of the favorite. |
| sortOrder | Float | The order of the item in the favorites list. |
| children | FavoriteConnection | Children of the favorite. Only applies to favorites of type folder. |
| issue | Issue | The favorited issue. |
| project | Project | The favorited project. |
| facet | Facet | [INTERNAL] The favorited facet. |
| projectTeam | Team | [DEPRECATED] The favorited team of the project. |
| cycle | Cycle | The favorited cycle. |
| customView | CustomView | The favorited custom view. |
| predefinedViewTeam | Team | The team of the favorited predefined view. |
| document | Document | The favorited document. |
| initiative | Initiative | The favorited initiative. |
| label | IssueLabel | The favorited label. |
| projectLabel | ProjectLabel | The favorited project label. |
| user | User | The favorited user. |
| customer | Customer | The favorited customer. |
| dashboard | Dashboard | The favorited dashboard. |
| pullRequest | PullRequest | The favorited pull request. |
| release | Release | [ALPHA] The favorited release. |
| releasePipeline | ReleasePipeline | [ALPHA] The favorited release pipeline. |
| url | String | URL of the favorited entity. Folders return 'null' value. |
| title | String | [Internal] Favorite's title text (name of the favorite'd object or folder). |
| detail | String | [Internal] Detail text for favorite's `title` (e.g. team's name for a project). |
| color | String | [Internal] Returns the color of the favorite's icon. Unavailable for avatars and views with fixed icons (e.g. cycle). |
| icon | String | [Internal] Name of the favorite's icon. Unavailable for standard views, issues, and avatars |

## FavoriteConnection
| Field | Type | Description |
|-------|------|-------------|
| edges | NON_NULL |  |
| nodes | NON_NULL |  |
| pageInfo | PageInfo |  |

## FavoritePayload
| Field | Type | Description |
|-------|------|-------------|
| lastSyncId | Float | The identifier of the last sync operation. |
| favorite | Favorite | The object that was added as a favorite. |
| success | Boolean | Whether the operation was successful. |

## Initiative
An initiative to group projects.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| updateReminderFrequencyInWeeks | Float | The n-weekly frequency at which to prompt for updates. When not set, reminders are inherited from workspace. |
| updateReminderFrequency | Float | The frequency at which to prompt for updates. When not set, reminders are inherited from workspace. |
| frequencyResolution | FrequencyResolutionType | The resolution of the reminder frequency. |
| updateRemindersDay | Day | The day at which to prompt for updates. |
| updateRemindersHour | Float | The hour at which to prompt for updates. |
| name | String | The name of the initiative. |
| description | String | The description of the initiative. |
| organization | Organization | The organization of the initiative. |
| creator | User | The user who created the initiative. |
| owner | User | The user who owns the initiative. |
| slugId | String | The initiative's unique URL slug. |
| sortOrder | Float | The sort order of the initiative within the organization. |
| color | String | The initiative's color. |
| icon | String | The icon of the initiative. |
| trashed | Boolean | A flag that indicates whether the initiative is in the trash bin. |
| facets | NON_NULL | [Internal] Facets associated with the initiative. |
| targetDate | TimelessDate | The estimated completion date of the initiative. |
| targetDateResolution | DateResolutionType | The resolution of the initiative's estimated completion date. |
| status | InitiativeStatus | The status of the initiative. One of Planned, Active, Completed |
| lastUpdate | InitiativeUpdate | The last initiative update posted for this initiative. |
| health | InitiativeUpdateHealthType | The health of the initiative. |
| healthUpdatedAt | DateTime | The time at which the initiative health was updated. |
| startedAt | DateTime | The time at which the initiative was moved into active status. |
| completedAt | DateTime | The time at which the initiative was moved into completed status. |
| url | String | Initiative URL. |
| projects | ProjectConnection | Projects associated with the initiative. |
| links | EntityExternalLinkConnection | Links associated with the initiative. |
| integrationsSettings | IntegrationsSettings | Settings for all integrations associated with that initiative. |
| history | InitiativeHistoryConnection | History entries associated with the initiative. |
| initiativeUpdates | InitiativeUpdateConnection | Initiative updates associated with the initiative. |
| subInitiatives | InitiativeConnection | Sub-initiatives associated with the initiative. |
| parentInitiative | Initiative | Parent initiative associated with the initiative. |
| parentInitiatives | InitiativeConnection | [Internal] Parent initiatives associated with the initiative. |
| content | String | The initiative's content in markdown format. |
| documentContent | DocumentContent | The content of the initiative description. |
| documents | DocumentConnection | Documents associated with the initiative. |

## InitiativeConnection
| Field | Type | Description |
|-------|------|-------------|
| edges | NON_NULL |  |
| nodes | NON_NULL |  |
| pageInfo | PageInfo |  |

## Integration
An integration with an external service.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| service | String | The integration's type. |
| organization | Organization | The organization that the integration is associated with. |
| team | Team | The team that the integration is associated with. |
| creator | User | The user that added the integration. |

## IntegrationConnection
| Field | Type | Description |
|-------|------|-------------|
| edges | NON_NULL |  |
| nodes | NON_NULL |  |
| pageInfo | PageInfo |  |

## Issue
An issue.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| number | Float | The issue's unique number. |
| title | String | The issue's title. |
| priority | Float | The priority of the issue. 0 = No priority, 1 = Urgent, 2 = High, 3 = Normal, 4 = Low. |
| estimate | Float | The estimate of the complexity of the issue.. |
| sortOrder | Float | The order of the item in relation to other items in the organization. |
| prioritySortOrder | Float | The order of the item in relation to other items in the organization, when ordered by priority. |
| startedAt | DateTime | The time at which the issue was moved into started state. |
| completedAt | DateTime | The time at which the issue was moved into completed state. |
| startedTriageAt | DateTime | The time at which the issue entered triage. |
| triagedAt | DateTime | The time at which the issue left triage. |
| canceledAt | DateTime | The time at which the issue was moved into canceled state. |
| autoClosedAt | DateTime | The time at which the issue was automatically closed by the auto pruning process. |
| autoArchivedAt | DateTime | The time at which the issue was automatically archived by the auto pruning process. |
| dueDate | TimelessDate | The date at which the issue is due. |
| slaStartedAt | DateTime | The time at which the issue's SLA began. |
| slaMediumRiskAt | DateTime | The time at which the issue's SLA will enter medium risk state. |
| slaHighRiskAt | DateTime | The time at which the issue's SLA will enter high risk state. |
| slaBreachesAt | DateTime | The time at which the issue's SLA will breach. |
| slaType | String | The type of SLA set on the issue. Calendar days or business days. |
| addedToProjectAt | DateTime | The time at which the issue was added to a project. |
| addedToCycleAt | DateTime | The time at which the issue was added to a cycle. |
| addedToTeamAt | DateTime | The time at which the issue was added to a team. |
| trashed | Boolean | A flag that indicates whether the issue is in the trash bin. |
| snoozedUntilAt | DateTime | The time until an issue will be snoozed in Triage view. |
| suggestionsGeneratedAt | DateTime | [Internal] The time at which the most recent suggestions for this issue were generated. |
| activitySummary | JSONObject | [Internal] The activity summary information for this issue. |
| summary | Summary | [Internal] AI-generated activity summary for this issue. |
| labelIds | NON_NULL | Id of the labels associated with this issue. |
| team | Team | The team that the issue is associated with. |
| cycle | Cycle | The cycle that the issue is associated with. |
| project | Project | The project that the issue is associated with. |
| projectMilestone | ProjectMilestone | The projectMilestone that the issue is associated with. |
| lastAppliedTemplate | Template | The last template that was applied to this issue. |
| recurringIssueTemplate | Template | The recurring issue template that created this issue. |
| previousIdentifiers | NON_NULL | Previous identifiers of the issue if it has been moved between teams. |
| creator | User | The user who created the issue. |
| externalUserCreator | ExternalUser | The external user who created the issue. |
| assignee | User | The user to whom the issue is assigned to. |
| delegate | User | The agent user that is delegated to work on this issue. |
| snoozedBy | User | The user who snoozed the issue. |
| state | WorkflowState | The workflow state that the issue is associated with. |
| subIssueSortOrder | Float | The order of the item in the sub-issue list. Only set if the issue has a parent. |
| reactionData | JSONObject | Emoji reaction summary, grouped by emoji type. |
| priorityLabel | String | Label for the priority. |
| sourceComment | Comment | The comment that this issue was created from. |
| integrationSourceType | IntegrationService | Integration type that created this issue, if applicable. |
| documents | DocumentConnection | Documents associated with the issue. |
| botActor | ActorBot | The bot that created the issue, if applicable. |
| favorite | Favorite | The users favorite associated with this issue. |
| identifier | String | Issue's human readable identifier (e.g. ENG-123). |
| url | String | Issue URL. |
| branchName | String | Suggested branch name for the issue. |
| sharedAccess | IssueSharedAccess | Shared access metadata for this issue. |
| customerTicketCount | Int | Returns the number of Attachment resources which are created by customer support ticketing systems (e.g. Zendesk). |
| subscribers | UserConnection | Users who are subscribed to the issue. |
| parent | Issue | The parent of the issue. |
| children | IssueConnection | Children of the issue. |
| comments | CommentConnection | Comments associated with the issue. |
| history | IssueHistoryConnection | History entries associated with the issue. |
| labels | IssueLabelConnection | Labels associated with this issue. |
| relations | IssueRelationConnection | Relations associated with this issue. |
| inverseRelations | IssueRelationConnection | Inverse relations associated with this issue. |
| attachments | AttachmentConnection | Attachments associated with the issue. |
| formerAttachments | AttachmentConnection | Attachments previously associated with the issue before being moved to another issue. |
| description | String | The issue's description in markdown format. |
| descriptionState | String | [Internal] The issue's description content as YJS state. |
| documentContent | DocumentContent | [ALPHA] The document content representing this issue description. |
| reactions | NON_NULL | Reactions associated with the issue. |
| needs | CustomerNeedConnection | Customer needs associated with the issue. |
| formerNeeds | CustomerNeedConnection | Customer needs previously associated with the issue before being moved to another issue. |
| syncedWith | LIST | The external services the issue is synced with. |
| suggestions | IssueSuggestionConnection | [Internal] Product Intelligence suggestions for the issue. |
| incomingSuggestions | IssueSuggestionConnection | [Internal] Incoming product intelligence relation suggestions for the issue. |
| asksRequester | User | The internal user who requested creation of the Asks issue on behalf of the creator. |
| asksExternalUserRequester | ExternalUser | The external user who requested creation of the Asks issue on behalf of the creator. |
| stateHistory | IssueStateSpanConnection | The issue's workflow states over time. |

## IssueConnection
| Field | Type | Description |
|-------|------|-------------|
| edges | NON_NULL |  |
| nodes | NON_NULL |  |
| pageInfo | PageInfo |  |

## IssueEdge
| Field | Type | Description |
|-------|------|-------------|
| node | Issue |  |
| cursor | String | Used in `before` and `after` args |

## IssueLabel
Labels that can be associated with issues.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| name | String | The label's name. |
| description | String | The label's description. |
| color | String | The label's color as a HEX string. |
| isGroup | Boolean | Whether the label is a group. |
| lastAppliedAt | DateTime | The date when the label was last applied to an issue or project. |
| retiredAt | DateTime | [Internal] When the label was retired. |
| team | Team | The team that the label is associated with. If null, the label is associated with the global workspace. |
| creator | User | The user who created the label. |
| retiredBy | User | The user who retired the label. |
| parent | IssueLabel | The parent label. |
| inheritedFrom | IssueLabel | The original label inherited from. |
| issues | IssueConnection | Issues associated with the label. |
| children | IssueLabelConnection | Children of the label. |

## IssueLabelConnection
| Field | Type | Description |
|-------|------|-------------|
| edges | NON_NULL |  |
| nodes | NON_NULL |  |
| pageInfo | PageInfo |  |

## IssueLabelPayload
| Field | Type | Description |
|-------|------|-------------|
| lastSyncId | Float | The identifier of the last sync operation. |
| issueLabel | IssueLabel | The label that was created or updated. |
| success | Boolean | Whether the operation was successful. |

## IssuePayload
| Field | Type | Description |
|-------|------|-------------|
| lastSyncId | Float | The identifier of the last sync operation. |
| issue | Issue | The issue that was created or updated. |
| success | Boolean | Whether the operation was successful. |

## IssueRelation
A relation between two issues.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| type | String | The relationship of the issue with the related issue. |
| issue | Issue | The issue whose relationship is being described. |
| relatedIssue | Issue | The related issue. |

## IssueRelationConnection
| Field | Type | Description |
|-------|------|-------------|
| edges | NON_NULL |  |
| nodes | NON_NULL |  |
| pageInfo | PageInfo |  |

## IssueRelationPayload
| Field | Type | Description |
|-------|------|-------------|
| lastSyncId | Float | The identifier of the last sync operation. |
| issueRelation | IssueRelation | The issue relation that was created or updated. |
| success | Boolean | Whether the operation was successful. |

## Notification
A notification sent to a user.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| type | String | Notification type. |
| actor | User | The user that caused the notification. |
| externalUserActor | ExternalUser | The external user that caused the notification. |
| user | User | The user that received the notification. |
| readAt | DateTime | The time at when the user marked the notification as read. Null, if the the user hasn't read the notification |
| emailedAt | DateTime | The time at when an email reminder for this notification was sent to the user. Null, if no email     reminder has been sent. |
| snoozedUntilAt | DateTime | The time until a notification will be snoozed. After that it will appear in the inbox again. |
| unsnoozedAt | DateTime | The time at which a notification was unsnoozed.. |
| category | NotificationCategory | The category of the notification. |
| url | String | [Internal] URL to the target of the notification. |
| inboxUrl | String | [Internal] Inbox URL for the notification. |
| title | String | [Internal] Notification title. |
| subtitle | String | [Internal] Notification subtitle. |
| isLinearActor | Boolean | [Internal] If notification actor was Linear. |
| actorAvatarUrl | String | [Internal] Notification avatar URL. |
| actorInitials | String | [Internal] Notification actor initials if avatar is not available. |
| actorAvatarColor | String | [Internal] Notification actor initials if avatar is not available. |
| issueStatusType | String | [Internal] Issue's status type for issue notifications. |
| projectUpdateHealth | String | [Internal] Project update health for new updates. |
| initiativeUpdateHealth | String | [Internal] Initiative update health for new updates. |
| groupingKey | String | [Internal] Notifications with the same grouping key will be grouped together in the UI. |
| groupingPriority | Float | [Internal] Priority of the notification with the same grouping key. Higher number means higher priority. If priority is the same, notifications should be sorted by `createdAt`. |
| botActor | ActorBot | The bot that caused the notification. |

## NotificationConnection
| Field | Type | Description |
|-------|------|-------------|
| edges | NON_NULL |  |
| nodes | NON_NULL |  |
| pageInfo | PageInfo |  |

## Organization
An organization. Organizations are root-level objects that contain user accounts and teams.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| name | String | The organization's name. |
| urlKey | String | The organization's unique URL key. |
| logoUrl | String | The organization's logo URL. |
| periodUploadVolume | Float | Rolling 30-day total upload volume for the organization, in megabytes. |
| facets | NON_NULL | [Internal] Facets associated with the organization. |
| gitBranchFormat | String | How git branches are formatted. If null, default formatting will be used. |
| gitLinkbackMessagesEnabled | Boolean | Whether the Git integration linkback messages should be sent to private repositories. |
| gitPublicLinkbackMessagesEnabled | Boolean | Whether the Git integration linkback messages should be sent to public repositories. |
| gitLinkbackDescriptionsEnabled | Boolean | Whether issue descriptions should be included in Git integration linkback messages. |
| roadmapEnabled | Boolean | Whether the organization is using a roadmap. |
| projectUpdateReminderFrequencyInWeeks | Float | The n-weekly frequency at which to prompt for project updates. When not set, reminders are off. |
| projectUpdateRemindersDay | Day | The day at which to prompt for project updates. |
| projectUpdateRemindersHour | Float | The hour at which to prompt for project updates. |
| initiativeUpdateReminderFrequencyInWeeks | Float | The n-weekly frequency at which to prompt for initiative updates. When not set, reminders are off. |
| initiativeUpdateRemindersDay | Day | The day at which to prompt for initiative updates. |
| initiativeUpdateRemindersHour | Float | The hour at which to prompt for initiative updates. |
| fiscalYearStartMonth | Float | The month at which the fiscal year starts. Defaults to January (0). |
| workingDays | NON_NULL | [Internal] The list of working days. Sunday is 0, Monday is 1, etc. |
| samlEnabled | Boolean | Whether SAML authentication is enabled for organization. |
| samlSettings | JSONObject | [INTERNAL] SAML settings. |
| scimEnabled | Boolean | Whether SCIM provisioning is enabled for organization. |
| scimSettings | JSONObject | [INTERNAL] SCIM settings. |
| securitySettings | JSONObject | Security settings for the organization. |
| allowedAuthServices | NON_NULL | Allowed authentication providers, empty array means all are allowed. |
| allowedFileUploadContentTypes | LIST | Allowed file upload content types |
| ipRestrictions | LIST | IP restriction configurations. |
| deletionRequestedAt | DateTime | The time at which deletion of the organization was requested. |
| trialEndsAt | DateTime | The time at which the trial will end. |
| trialStartsAt | DateTime | The time at which the trial started. |
| previousUrlKeys | NON_NULL | Previously used URL keys for the organization (last 3 are kept and redirected). |
| hipaaComplianceEnabled | Boolean | Whether HIPAA compliance is enabled for organization. |
| themeSettings | JSONObject | [ALPHA] Theme settings for the organization. |
| releaseChannel | ReleaseChannel | The feature release channel the organization belongs to. |
| customersConfiguration | JSONObject | Configuration settings for the Customers feature. |
| codeIntelligenceEnabled | Boolean | [INTERNAL] Whether code intelligence is enabled for the organization. |
| codeIntelligenceRepository | String | [INTERNAL] GitHub repository in owner/repo format for code intelligence. |
| defaultFeedSummarySchedule | FeedSummarySchedule | Default schedule for how often feed summaries are generated. |
| feedEnabled | Boolean | Whether the organization has enabled the feed feature. |
| hideNonPrimaryOrganizations | Boolean | Whether to hide other organizations for new users signing up with email domains claimed by this organization. |
| aiAddonEnabled | Boolean | [INTERNAL] Whether the organization has enabled the AI add-on (which at this point only includes triage suggestions). |
| generatedUpdatesEnabled | Boolean | [INTERNAL] Whether the organization has enabled generated updates. |
| aiThreadSummariesEnabled | Boolean | Whether the organization has enabled resolved thread AI summaries. |
| aiDiscussionSummariesEnabled | Boolean | Whether the organization has enabled AI discussion summaries for issues. |
| aiProviderConfiguration | JSONObject | [INTERNAL] Configure per-modality AI host providers and model families. |
| linearAgentEnabled | Boolean | [Internal] Whether the organization has enabled Linear Agent. |
| users | UserConnection | Users associated with the organization. |
| teams | TeamConnection | Teams associated with the organization. |
| projectStatuses | NON_NULL | The organization's project statuses. |
| integrations | IntegrationConnection | Integrations associated with the organization. |
| slackProjectChannelIntegration | Integration | The Slack integration used for auto-creating project channels. |
| slackProjectChannelPrefix | String | The prefix used for auto-created Slack project channels. |
| subscription | PaidSubscription | The organization's subscription to a paid plan. |
| userCount | Int | Number of active users in the organization. |
| createdIssueCount | Int | Aproximate number of issues in the organization, including archived ones. |
| templates | TemplateConnection | Templates associated with the organization. |
| labels | IssueLabelConnection | Labels associated with the organization. |
| projectLabels | ProjectLabelConnection | Project labels associated with the organization. |
| customerCount | Int | Number of customers in the organization. |
| customersEnabled | Boolean | Whether the organization is using Customers. |

## PageInfo
| Field | Type | Description |
|-------|------|-------------|
| hasPreviousPage | Boolean | Indicates if there are more results when paginating backward. |
| hasNextPage | Boolean | Indicates if there are more results when paginating forward. |
| startCursor | String | Cursor representing the first result in the paginated results. |
| endCursor | String | Cursor representing the last result in the paginated results. |

## Project
A project.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| updateReminderFrequencyInWeeks | Float | The n-weekly frequency at which to prompt for updates. When not set, reminders are inherited from workspace. |
| updateReminderFrequency | Float | The frequency at which to prompt for updates. When not set, reminders are inherited from workspace. |
| frequencyResolution | FrequencyResolutionType | The resolution of the reminder frequency. |
| updateRemindersDay | Day | The day at which to prompt for updates. |
| updateRemindersHour | Float | The hour at which to prompt for updates. |
| name | String | The project's name. |
| description | String | The project's description. |
| slugId | String | The project's unique URL slug. |
| icon | String | The icon of the project. |
| color | String | The project's color. |
| status | ProjectStatus | The status that the project is associated with. |
| creator | User | The user who created the project. |
| lead | User | The project lead. |
| facets | NON_NULL | [Internal] Facets associated with the project. |
| projectUpdateRemindersPausedUntilAt | DateTime | The time until which project update reminders are paused. |
| startDate | TimelessDate | The estimated start date of the project. |
| startDateResolution | DateResolutionType | The resolution of the project's start date. |
| targetDate | TimelessDate | The estimated completion date of the project. |
| targetDateResolution | DateResolutionType | The resolution of the project's estimated completion date. |
| startedAt | DateTime | The time at which the project was moved into started state. |
| completedAt | DateTime | The time at which the project was moved into completed state. |
| canceledAt | DateTime | The time at which the project was moved into canceled state. |
| autoArchivedAt | DateTime | The time at which the project was automatically archived by the auto pruning process. |
| trashed | Boolean | A flag that indicates whether the project is in the trash bin. |
| sortOrder | Float | The sort order for the project within the organization. |
| prioritySortOrder | Float | The sort order for the project within the organization, when ordered by priority. |
| convertedFromIssue | Issue | The project was created based on this issue. |
| lastAppliedTemplate | Template | The last template that was applied to this project. |
| priority | Int | The priority of the project. 0 = No priority, 1 = Urgent, 2 = High, 3 = Normal, 4 = Low. |
| lastUpdate | ProjectUpdate | The last project update posted for this project. |
| health | ProjectUpdateHealthType | The health of the project. |
| healthUpdatedAt | DateTime | The time at which the project health was updated. |
| issueCountHistory | NON_NULL | The total number of issues in the project after each week. |
| completedIssueCountHistory | NON_NULL | The number of completed issues in the project after each week. |
| scopeHistory | NON_NULL | The total number of estimation points after each week. |
| completedScopeHistory | NON_NULL | The number of completed estimation points after each week. |
| inProgressScopeHistory | NON_NULL | The number of in progress estimation points after each week. |
| progressHistory | JSONObject | [INTERNAL] The progress history of the project. |
| currentProgress | JSONObject | [INTERNAL] The current progress of the project. |
| labelIds | NON_NULL | Id of the labels associated with this project. |
| favorite | Favorite | The user's favorite associated with this project. |
| url | String | Project URL. |
| initiatives | InitiativeConnection | Initiatives that this project belongs to. |
| initiativeToProjects | InitiativeToProjectConnection | Associations of this project to parent initiatives. |
| teams | TeamConnection | Teams associated with this project. |
| members | UserConnection | Users that are members of the project. |
| projectUpdates | ProjectUpdateConnection | Project updates associated with the project. |
| documents | DocumentConnection | Documents associated with the project. |
| projectMilestones | ProjectMilestoneConnection | Milestones associated with the project. |
| issues | IssueConnection | Issues associated with the project. |
| externalLinks | EntityExternalLinkConnection | External links associated with the project. |
| attachments | ProjectAttachmentConnection | Attachments associated with the project. |
| history | ProjectHistoryConnection | History entries associated with the project. |
| labels | ProjectLabelConnection | Labels associated with this project. |
| progress | Float | The overall progress of the project. This is the (completed estimate points + 0.25 * in progress estimate points) / total estimate points. |
| scope | Float | The overall scope (total estimate points) of the project. |
| integrationsSettings | IntegrationsSettings | Settings for all integrations associated with that project. |
| content | String | The project's content in markdown format. |
| contentState | String | [Internal] The project's content as YJS state. |
| documentContent | DocumentContent | The content of the project description. |
| comments | CommentConnection | Comments associated with the project overview. |
| relations | ProjectRelationConnection | Relations associated with this project. |
| inverseRelations | ProjectRelationConnection | Inverse relations associated with this project. |
| needs | CustomerNeedConnection | Customer needs associated with the project. |
| priorityLabel | String | The priority of the project as a label. |
| syncedWith | LIST | The external services the project is synced with. |

## ProjectConnection
| Field | Type | Description |
|-------|------|-------------|
| edges | NON_NULL |  |
| nodes | NON_NULL |  |
| pageInfo | PageInfo |  |

## ProjectMilestone
A milestone for a project.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| name | String | The name of the project milestone. |
| documentContent | DocumentContent | The content of the project milestone description. |
| targetDate | TimelessDate | The planned completion date of the milestone. |
| project | Project | The project of the milestone. |
| progressHistory | JSONObject | [Internal] The progress history of the project milestone. |
| currentProgress | JSONObject | [Internal] The current progress of the project milestone. |
| sortOrder | Float | The order of the milestone in relation to other milestones within a project. |
| description | String | The project milestone's description in markdown format. |
| status | ProjectMilestoneStatus | The status of the project milestone. |
| progress | Float | The progress % of the project milestone. |
| descriptionState | String | [Internal] The project milestone's description as YJS state. |
| issues | IssueConnection | Issues associated with the project milestone. |

## ProjectPayload
| Field | Type | Description |
|-------|------|-------------|
| lastSyncId | Float | The identifier of the last sync operation. |
| project | Project | The project that was created or updated. |
| success | Boolean | Whether the operation was successful. |

## ProjectUpdate
An update associated with a project.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| body | String | The update content in markdown format. |
| editedAt | DateTime | The time the update was edited. |
| reactionData | JSONObject | Emoji reaction summary, grouped by emoji type. |
| bodyData | String | [Internal] The content of the update as a Prosemirror document. |
| slugId | String | The update's unique URL slug. |
| project | Project | The project that the update is associated with. |
| health | ProjectUpdateHealthType | The health of the project at the time of the update. |
| user | User | The user who wrote the update. |
| infoSnapshot | JSONObject | [Internal] Serialized JSON representing current state of the project properties when posting the project update. |
| isDiffHidden | Boolean | Whether project update diff should be hidden. |
| url | String | The URL to the project update. |
| isStale | Boolean | Whether the project update is stale. |
| diff | JSONObject | The diff between the current update and the previous one. |
| diffMarkdown | String | The diff between the current update and the previous one, formatted as markdown. |
| reactions | NON_NULL | Reactions associated with the project update. |
| comments | CommentConnection | Comments associated with the project update. |
| commentCount | Int | Number of comments associated with the project update. |

## Roadmap
[Deprecated] A roadmap for projects.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| name | String | The name of the roadmap. |
| description | String | The description of the roadmap. |
| organization | Organization | The organization of the roadmap. |
| creator | User | The user who created the roadmap. |
| owner | User | The user who owns the roadmap. |
| slugId | String | The roadmap's unique URL slug. |
| sortOrder | Float | The sort order of the roadmap within the organization. |
| color | String | The roadmap's color. |
| projects | ProjectConnection | Projects associated with the roadmap. |
| url | String | The canonical url for the roadmap. |

## RoadmapPayload
| Field | Type | Description |
|-------|------|-------------|
| lastSyncId | Float | The identifier of the last sync operation. |
| roadmap | Roadmap | The roadmap that was created or updated. |
| success | Boolean | Whether the operation was successful. |

## Team
An organizational unit that contains issues.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| name | String | The team's name. |
| key | String | The team's unique key. The key is used in URLs. |
| description | String | The team's description. |
| icon | String | The icon of the team. |
| color | String | The team's color. |
| retiredAt | DateTime | The time at which the team was retired. Null if the team has not been retired. |
| organization | Organization | The organization that the team is associated with. |
| parent | Team | [Internal] The team's parent team. |
| children | NON_NULL | [Internal] The team's sub-teams. |
| cyclesEnabled | Boolean | Whether the team uses cycles. |
| cycleStartDay | Float | The day of the week that a new cycle starts. |
| cycleDuration | Float | The duration of a cycle in weeks. |
| cycleCooldownTime | Float | The cooldown time after each cycle in weeks. |
| cycleIssueAutoAssignStarted | Boolean | Auto assign started issues to current cycle. |
| cycleIssueAutoAssignCompleted | Boolean | Auto assign completed issues to current cycle. |
| cycleLockToActive | Boolean | Auto assign issues to current cycle if in active status. |
| upcomingCycleCount | Float | How many upcoming cycles to create. |
| timezone | String | The timezone of the team. Defaults to "America/Los_Angeles" |
| inheritWorkflowStatuses | Boolean | Whether the team should inherit its workflow statuses from its parent. Only applies to sub-teams. |
| inheritIssueEstimation | Boolean | Whether the team should inherit its estimation settings from its parent. Only applies to sub-teams. |
| issueEstimationType | String | The issue estimation type to use. Must be one of "notUsed", "exponential", "fibonacci", "linear", "tShirt". |
| issueEstimationAllowZero | Boolean | Whether to allow zeros in issues estimates. |
| setIssueSortOrderOnStateChange | String | Where to move issues when changing state. |
| issueEstimationExtended | Boolean | Whether to add additional points to the estimate scale. |
| defaultIssueEstimate | Float | What to use as a default estimate for unestimated issues. |
| triageEnabled | Boolean | Whether triage mode is enabled for the team or not. |
| requirePriorityToLeaveTriage | Boolean | Whether an issue needs to have a priority set before leaving triage. |
| defaultIssueState | WorkflowState | The default workflow state into which issues are set when they are opened by team members. |
| defaultTemplateForMembers | Template | The default template to use for new issues created by members of the team. |
| defaultTemplateForNonMembers | Template | The default template to use for new issues created by non-members of the team. |
| defaultProjectTemplate | Template | The default template to use for new projects created for the team. |
| triageIssueState | WorkflowState | The workflow state into which issues are set when they are opened by non-team members or integrations if triage is enabled. |
| private | Boolean | Whether the team is private or not. |
| allMembersCanJoin | Boolean | Whether all members in the workspace can join the team. Only used for public teams. |
| securitySettings | JSONObject | Security settings for the team. |
| facets | NON_NULL | [Internal] Facets associated with the team. |
| posts | NON_NULL | [Internal] Posts associated with the team. |
| scimManaged | Boolean | Whether the team is managed by SCIM integration. |
| scimGroupName | String | The SCIM group name for the team. |
| progressHistory | JSONObject | [Internal] The progress history of the team. |
| currentProgress | JSONObject | [Internal] The current progress of the team. |
| groupIssueHistory | Boolean | Whether to group recent issue history entries. |
| aiThreadSummariesEnabled | Boolean | Whether to enable resolved thread AI summaries. |
| aiDiscussionSummariesEnabled | Boolean | Whether to enable AI discussion summaries for issues in this team. |
| autoClosePeriod | Float | Period after which issues are automatically closed in months. Null/undefined means disabled. |
| autoCloseStateId | String | The canceled workflow state which auto closed issues will be set to. Defaults to the first canceled state. |
| autoArchivePeriod | Float | Period after which automatically closed and completed issues are automatically archived in months. |
| autoCloseParentIssues | Boolean | Whether parent issues should automatically close when all child issues are closed |
| autoCloseChildIssues | Boolean | Whether child issues should automatically close when their parent issue is closed |
| markedAsDuplicateWorkflowState | WorkflowState | The workflow state into which issues are moved when they are marked as a duplicate of another issue. Defaults to the first canceled state. |
| joinByDefault | Boolean | [Internal] Whether new users should join this team by default. |
| cycleCalenderUrl | String | Calendar feed URL (iCal) for cycles. |
| displayName | String | The name of the team including its parent team name if it has one. |
| issues | IssueConnection | Issues associated with the team. |
| issueCount | Int | Number of issues in the team. |
| cycles | CycleConnection | Cycles associated with the team. |
| activeCycle | Cycle | Team's currently active cycle. |
| triageResponsibility | TriageResponsibility | Team's triage responsibility. |
| members | UserConnection | Users who are members of this team. |
| membership | TeamMembership | [ALPHA] The membership of the given user in the team. |
| memberships | TeamMembershipConnection | Memberships associated with the team. For easier access of the same data, use `members` query. |
| projects | ProjectConnection | Projects associated with the team. |
| states | WorkflowStateConnection | The states that define the workflow associated with the team. |
| gitAutomationStates | GitAutomationStateConnection | The Git automation states for the team. |
| templates | TemplateConnection | Templates associated with the team. |
| labels | IssueLabelConnection | Labels associated with the team. |
| webhooks | WebhookConnection | Webhooks associated with the team. |
| integrationsSettings | IntegrationsSettings | Settings for all integrations associated with that team. |

## TeamConnection
| Field | Type | Description |
|-------|------|-------------|
| edges | NON_NULL |  |
| nodes | NON_NULL |  |
| pageInfo | PageInfo |  |

## TeamPayload
| Field | Type | Description |
|-------|------|-------------|
| lastSyncId | Float | The identifier of the last sync operation. |
| team | Team | The team that was created or updated. |
| success | Boolean | Whether the operation was successful. |

## User
A user that has access to the the resources of an organization.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| name | String | The user's full name. |
| displayName | String | The user's display (nick) name. Unique within each organization. |
| email | String | The user's email address. |
| avatarUrl | String | An URL to the user's avatar image. |
| disableReason | String | Reason why is the account disabled. |
| calendarHash | String | [DEPRECATED] Hash for the user to be used in calendar URLs. |
| description | String | A short description of the user, either its title or bio. |
| statusEmoji | String | The emoji to represent the user current status. |
| statusLabel | String | The label of the user current status. |
| statusUntilAt | DateTime | A date at which the user current status should be cleared. |
| timezone | String | The local timezone of the user. |
| organization | Organization | Organization the user belongs to. |
| lastSeen | DateTime | The last time the user was seen online. |
| identityProvider | IdentityProvider | [INTERNAL] Identity provider the user is managed by. |
| initials | String | The initials of the user. |
| avatarBackgroundColor | String | The background color of the avatar for users without set avatar. |
| guest | Boolean | Whether the user is a guest in the workspace and limited to accessing a subset of teams. |
| app | Boolean | Whether the user is an app. |
| isMentionable | Boolean | Whether the user is mentionable. |
| isAssignable | Boolean | Whether the user is assignable. |
| active | Boolean | Whether the user account is active or disabled (suspended). |
| issueDrafts | IssueDraftConnection | The user's issue drafts |
| drafts | DraftConnection | The user's drafts |
| url | String | User's profile URL. |
| assignedIssues | IssueConnection | Issues assigned to the user. |
| delegatedIssues | IssueConnection | Issues delegated to this user. |
| createdIssues | IssueConnection | Issues created by the user. |
| createdIssueCount | Int | Number of issues created. |
| teams | TeamConnection | Teams the user is part of. |
| teamMemberships | TeamMembershipConnection | Memberships associated with the user. For easier access of the same data, use `teams` query. |
| feedFacets | FacetConnection | [INTERNAL] The user's pinned feeds. |
| canAccessAnyPublicTeam | Boolean | Whether this user can access any public team in the organization. |
| isMe | Boolean | Whether the user is the currently authenticated user. |
| admin | Boolean | Whether the user is an organization administrator. |
| owner | Boolean | Whether the user is an organization owner. |
| supportsAgentSessions | Boolean | Whether this agent user supports agent sessions. |
| gitHubUserId | String | The user's GitHub user ID. |

## UserConnection
| Field | Type | Description |
|-------|------|-------------|
| edges | NON_NULL |  |
| nodes | NON_NULL |  |
| pageInfo | PageInfo |  |

## WorkflowState
A state in a team workflow.

| Field | Type | Description |
|-------|------|-------------|
| id | ID | The unique identifier of the entity. |
| createdAt | DateTime | The time at which the entity was created. |
| updatedAt | DateTime | The last time at which the entity was meaningfully updated. This is the same as the creation time if the entity hasn't     been updated after creation. |
| archivedAt | DateTime | The time at which the entity was archived. Null if the entity has not been archived. |
| name | String | The state's name. |
| color | String | The state's UI color as a HEX string. |
| description | String | Description of the state. |
| position | Float | The position of the state in the team flow. |
| type | String | The type of the state. One of "triage", "backlog", "unstarted", "started", "completed", "canceled". |
| team | Team | The team to which this state belongs to. |
| inheritedFrom | WorkflowState | The state inherited from |
| issues | IssueConnection | Issues belonging in this state. |

## WorkflowStateConnection
| Field | Type | Description |
|-------|------|-------------|
| edges | NON_NULL |  |
| nodes | NON_NULL |  |
| pageInfo | PageInfo |  |

## WorkflowStatePayload
| Field | Type | Description |
|-------|------|-------------|
| lastSyncId | Float | The identifier of the last sync operation. |
| workflowState | WorkflowState | The state that was created or updated. |
| success | Boolean | Whether the operation was successful. |


---


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


---


# Linear GraphQL API — Input Types

## AgentSessionCreateOnComment
| Field | Type | Description |
|-------|------|-------------|
| commentId | String | The root comment that this session will be associated with. |
| externalLink | String | The URL of an external agent-hosted page associated with this session. |
| externalUrls | LIST | URLs of external resources associated with this session. |

## AgentSessionCreateOnIssue
| Field | Type | Description |
|-------|------|-------------|
| issueId | String | The issue that this session will be associated with. Can be a UUID or issue identifier (e.g., 'LIN-123'). |
| externalLink | String | The URL of an external agent-hosted page associated with this session. |
| externalUrls | LIST | URLs of external resources associated with this session. |

## AttachmentCollectionFilter
Attachment collection filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| title | StringComparator | Comparator for the title. |
| subtitle | NullableStringComparator | Comparator for the subtitle. |
| url | StringComparator | Comparator for the url. |
| creator | NullableUserFilter | Filters that the attachments creator must satisfy. |
| sourceType | SourceTypeComparator | Comparator for the source type. |
| and | LIST | Compound filters, all of which need to be matched by the attachment. |
| or | LIST | Compound filters, one of which need to be matched by the attachment. |
| some | AttachmentFilter | Filters that needs to be matched by some attachments. |
| every | AttachmentFilter | Filters that needs to be matched by all attachments. |
| length | NumberComparator | Comparator for the collection length. |

## AttachmentCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| title | String | The attachment title. |
| subtitle | String | The attachment subtitle. |
| url | String | Attachment location which is also used as an unique identifier for the attachment. If another attachment is created with the same `url` value, existing record is updated instead. |
| issueId | String | The issue to associate the attachment with. Can be a UUID or issue identifier (e.g., 'LIN-123'). |
| iconUrl | String | An icon url to display with the attachment. Should be of jpg or png format. Maximum of 1MB in size. Dimensions should be 20x20px for optimal display quality. |
| metadata | JSONObject | Attachment metadata object with string and number values. |
| groupBySource | Boolean | Indicates if attachments for the same source application should be grouped in the Linear UI. |
| commentBody | String | Create a linked comment with markdown body. |
| commentBodyData | JSONObject | [Internal] Create a linked comment with Prosemirror body. Please use `commentBody` instead. |
| createAsUser | String | Create attachment as a user with the provided name. This option is only available to OAuth applications creating attachments in `actor=application` mode. |

## AttachmentFilter
Attachment filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| title | StringComparator | Comparator for the title. |
| subtitle | NullableStringComparator | Comparator for the subtitle. |
| url | StringComparator | Comparator for the url. |
| creator | NullableUserFilter | Filters that the attachments creator must satisfy. |
| sourceType | SourceTypeComparator | Comparator for the source type. |
| and | LIST | Compound filters, all of which need to be matched by the attachment. |
| or | LIST | Compound filters, one of which need to be matched by the attachment. |

## AttachmentUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| title | String | The attachment title. |
| subtitle | String | The attachment subtitle. |
| metadata | JSONObject | Attachment metadata object with string and number values. |
| iconUrl | String | An icon url to display with the attachment. Should be of jpg or png format. Maximum of 1MB in size. Dimensions should be 20x20px for optimal display quality. |

## CommentCollectionFilter
Comment filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| body | StringComparator | Comparator for the comment's body. |
| user | UserFilter | Filters that the comment's creator must satisfy. |
| issue | NullableIssueFilter | Filters that the comment's issue must satisfy. |
| projectUpdate | NullableProjectUpdateFilter | Filters that the comment's project update must satisfy. |
| parent | NullableCommentFilter | Filters that the comment parent must satisfy. |
| documentContent | NullableDocumentContentFilter | Filters that the comment's document content must satisfy. |
| reactions | ReactionCollectionFilter | Filters that the comment's reactions must satisfy. |
| needs | CustomerNeedCollectionFilter | Filters that the comment's customer needs must satisfy. |
| and | LIST | Compound filters, all of which need to be matched by the comment. |
| or | LIST | Compound filters, one of which need to be matched by the comment. |
| some | CommentFilter | Filters that needs to be matched by some comments. |
| every | CommentFilter | Filters that needs to be matched by all comments. |
| length | NumberComparator | Comparator for the collection length. |

## CommentCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| body | String | The comment content in markdown format. |
| bodyData | JSON | [Internal] The comment content as a Prosemirror document. |
| issueId | String | The issue to associate the comment with. Can be a UUID or issue identifier (e.g., 'LIN-123'). |
| projectUpdateId | String | The project update to associate the comment with. |
| initiativeUpdateId | String | The initiative update to associate the comment with. |
| postId | String | The post to associate the comment with. |
| documentContentId | String | The document content to associate the comment with. |
| parentId | String | The parent comment under which to nest a current comment. |
| createAsUser | String | Create comment as a user with the provided name. This option is only available to OAuth applications creating comments in `actor=app` mode. |
| displayIconUrl | String | Provide an external user avatar URL. Can only be used in conjunction with the `createAsUser` options. This option is only available to OAuth applications creating comments in `actor=app` mode. |
| createdAt | DateTime | The date when the comment was created (e.g. if importing from another system). Must be a date in the past. If none is provided, the backend will generate the time as now. |
| doNotSubscribeToIssue | Boolean | Flag to prevent auto subscription to the issue the comment is created on. |
| createOnSyncedSlackThread | Boolean | Flag to indicate this comment should be created on the issue's synced Slack comment thread. If no synced Slack comment thread exists, the mutation will fail. |
| quotedText | String | The text that this comment references. Only defined for inline comments. |
| subscriberIds | LIST | [INTERNAL] The identifiers of the users subscribing to this comment thread. |

## CommentFilter
Comment filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| body | StringComparator | Comparator for the comment's body. |
| user | UserFilter | Filters that the comment's creator must satisfy. |
| issue | NullableIssueFilter | Filters that the comment's issue must satisfy. |
| projectUpdate | NullableProjectUpdateFilter | Filters that the comment's project update must satisfy. |
| parent | NullableCommentFilter | Filters that the comment parent must satisfy. |
| documentContent | NullableDocumentContentFilter | Filters that the comment's document content must satisfy. |
| reactions | ReactionCollectionFilter | Filters that the comment's reactions must satisfy. |
| needs | CustomerNeedCollectionFilter | Filters that the comment's customer needs must satisfy. |
| and | LIST | Compound filters, all of which need to be matched by the comment. |
| or | LIST | Compound filters, one of which need to be matched by the comment. |

## CommentUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| body | String | The comment content. |
| bodyData | JSON | [Internal] The comment content as a Prosemirror document. |
| resolvingUserId | String | [INTERNAL] The user who resolved this thread. |
| resolvingCommentId | String | [INTERNAL] The child comment that resolves this thread. |
| quotedText | String | The text that this comment references. Only defined for inline comments. |
| subscriberIds | LIST | [INTERNAL] The identifiers of the users subscribing to this comment. |
| doNotSubscribeToIssue | Boolean | [INTERNAL] Flag to prevent auto subscription to the issue the comment is updated on. |

## CustomerNeedCreateFromAttachmentInput
| Field | Type | Description |
|-------|------|-------------|
| attachmentId | String | The attachment this need is created from. |

## CycleCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| name | String | The custom name of the cycle. |
| description | String | The description of the cycle. |
| teamId | String | The team to associate the cycle with. |
| startsAt | DateTime | The start date of the cycle. |
| endsAt | DateTime | The end date of the cycle. |
| completedAt | DateTime | The completion time of the cycle. If null, the cycle hasn't been completed. |

## CycleFilter
Cycle filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| number | NumberComparator | Comparator for the cycle number. |
| name | StringComparator | Comparator for the cycle name. |
| startsAt | DateComparator | Comparator for the cycle start date. |
| endsAt | DateComparator | Comparator for the cycle ends at date. |
| completedAt | DateComparator | Comparator for the cycle completed at date. |
| isActive | BooleanComparator | Comparator for the filtering active cycle. |
| isInCooldown | BooleanComparator | Comparator for filtering for whether the cycle is currently in cooldown. |
| isNext | BooleanComparator | Comparator for the filtering next cycle. |
| isPrevious | BooleanComparator | Comparator for the filtering previous cycle. |
| isFuture | BooleanComparator | Comparator for the filtering future cycles. |
| isPast | BooleanComparator | Comparator for the filtering past cycles. |
| team | TeamFilter | Filters that the cycles team must satisfy. |
| issues | IssueCollectionFilter | Filters that the cycles issues must satisfy. |
| inheritedFromId | IDComparator | Comparator for the inherited cycle ID. |
| and | LIST | Compound filters, all of which need to be matched by the cycle. |
| or | LIST | Compound filters, one of which need to be matched by the cycle. |

## CyclePeriodComparator
Comparator for period when issue was added to a cycle.

| Field | Type | Description |
|-------|------|-------------|
| eq | CyclePeriod | Equals constraint. |
| neq | CyclePeriod | Not-equals constraint. |
| in | LIST | In-array constraint. |
| nin | LIST | Not-in-array constraint. |
| null | Boolean | Null constraint. Matches any non-null values if the given value is false, otherwise it matches null values. |

## CycleShiftAllInput
Input for shifting all cycles from a certain cycle onwards by a certain number of days

| Field | Type | Description |
|-------|------|-------------|
| id | String | The cycle ID at which to start the shift. |
| daysToShift | Float | The number of days to shift the cycles by. |

## CycleSort
Issue cycle sorting options.

| Field | Type | Description |
|-------|------|-------------|
| nulls | PaginationNulls | Whether nulls should be sorted first or last |
| order | PaginationSortOrder | The order for the individual sort |
| currentCycleFirst | Boolean | When set to true, cycles will be ordered with a custom order. Current cycle comes first, followed by upcoming cycles in ASC order, followed by previous cycles in DESC order. |

## CycleUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| name | String | The custom name of the cycle. |
| description | String | The description of the cycle. |
| startsAt | DateTime | The start date of the cycle. |
| endsAt | DateTime | The end date of the cycle. |
| completedAt | DateTime | The end date of the cycle. |

## DocumentCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| title | String | The title of the document. |
| icon | String | The icon of the document. |
| color | String | The color of the icon. |
| content | String | The document content as markdown. |
| projectId | String | Related project for the document. |
| initiativeId | String | [Internal] Related initiative for the document. |
| teamId | String | [Internal] Related team for the document. |
| issueId | String | Related issue for the document. Can be a UUID or issue identifier (e.g., 'LIN-123'). |
| releaseId | String | [Internal] Related release for the document. |
| cycleId | String | [Internal] Related cycle for the document. |
| resourceFolderId | String | [Internal] The resource folder containing the document. |
| lastAppliedTemplateId | String | The ID of the last template applied to the document. |
| sortOrder | Float | The order of the item in the resources list. |
| subscriberIds | LIST | [INTERNAL] The identifiers of the users subscribing to this document. |

## DocumentFilter
Document filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| title | StringComparator | Comparator for the document title. |
| slugId | StringComparator | Comparator for the document slug ID. |
| creator | UserFilter | Filters that the document's creator must satisfy. |
| project | ProjectFilter | Filters that the document's project must satisfy. |
| issue | IssueFilter | Filters that the document's issue must satisfy. |
| initiative | InitiativeFilter | Filters that the document's initiative must satisfy. |
| and | LIST | Compound filters, all of which need to be matched by the document. |
| or | LIST | Compound filters, one of which need to be matched by the document. |

## DocumentUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| title | String | The title of the document. |
| icon | String | The icon of the document. |
| color | String | The color of the icon. |
| content | String | The document content as markdown. |
| projectId | String | Related project for the document. |
| initiativeId | String | [Internal] Related initiative for the document. |
| teamId | String | [Internal] Related team for the document. |
| issueId | String | Related issue for the document. Can be a UUID or issue identifier (e.g., 'LIN-123'). |
| releaseId | String | [Internal] Related release for the document. |
| cycleId | String | [Internal] Related cycle for the document. |
| resourceFolderId | String | [Internal] The resource folder containing the document. |
| lastAppliedTemplateId | String | The ID of the last template applied to the document. |
| hiddenAt | DateTime | The time at which the document was hidden. |
| sortOrder | Float | The order of the item in the resources list. |
| trashed | Boolean | Whether the document has been trashed. |
| subscriberIds | LIST | [INTERNAL] The identifiers of the users subscribing to this document. |

## FavoriteCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier. If none is provided, the backend will generate one. |
| folderName | String | The name of the favorite folder. |
| parentId | String | The parent folder of the favorite. |
| issueId | String | The identifier of the issue to favorite. Can be a UUID or issue identifier (e.g., 'LIN-123'). |
| facetId | String | The identifier of the facet to favorite. |
| projectId | String | The identifier of the project to favorite. |
| projectTab | ProjectTab | The tab of the project to favorite. |
| predefinedViewType | String | The type of the predefined view to favorite. |
| predefinedViewTeamId | String | The identifier of team for the predefined view to favorite. |
| cycleId | String | The identifier of the cycle to favorite. |
| customViewId | String | The identifier of the custom view to favorite. |
| documentId | String | The identifier of the document to favorite. |
| initiativeId | String | [INTERNAL] The identifier of the initiative to favorite. |
| initiativeTab | InitiativeTab | The tab of the initiative to favorite. |
| labelId | String | The identifier of the label to favorite. |
| projectLabelId | String | The identifier of the label to favorite. |
| userId | String | The identifier of the user to favorite. |
| sortOrder | Float | The position of the item in the favorites list. |
| customerId | String | The identifier of the customer to favorite. |
| dashboardId | String | The identifier of the dashboard to favorite. |
| pullRequestId | String | The identifier of the pull request to favorite. |
| releaseId | String | [ALPHA] The identifier of the release to favorite. |
| releasePipelineId | String | [ALPHA] The identifier of the release pipeline to favorite. |

## FavoriteUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| sortOrder | Float | The position of the item in the favorites list. |
| parentId | String | The identifier (in UUID v4 format) of the folder to move the favorite under. |
| folderName | String | The name of the favorite folder. |

## InitiativeToProjectCreateInput
The properties of the initiativeToProject to create.

| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| projectId | String | The identifier of the project. |
| initiativeId | String | The identifier of the initiative. |
| sortOrder | Float | The sort order for the project within its organization. |

## InitiativeToProjectUpdateInput
The properties of the initiativeToProject to update.

| Field | Type | Description |
|-------|------|-------------|
| sortOrder | Float | The sort order for the project within its organization. |

## IssueBatchCreateInput
| Field | Type | Description |
|-------|------|-------------|
| issues | NON_NULL | The issues to create. |

## IssueCollectionFilter
Issue filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IssueIDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| number | NumberComparator | Comparator for the issues number. |
| title | StringComparator | Comparator for the issues title. |
| description | NullableStringComparator | Comparator for the issues description. |
| priority | NullableNumberComparator | Comparator for the issues priority. 0 = No priority, 1 = Urgent, 2 = High, 3 = Normal, 4 = Low. |
| estimate | EstimateComparator | Comparator for the issues estimate. |
| startedAt | NullableDateComparator | Comparator for the issues started at date. |
| triagedAt | NullableDateComparator | Comparator for the issues triaged at date. |
| completedAt | NullableDateComparator | Comparator for the issues completed at date. |
| canceledAt | NullableDateComparator | Comparator for the issues canceled at date. |
| archivedAt | NullableDateComparator | Comparator for the issues archived at date. |
| autoClosedAt | NullableDateComparator | Comparator for the issues auto closed at date. |
| autoArchivedAt | NullableDateComparator | Comparator for the issues auto archived at date. |
| addedToCycleAt | NullableDateComparator | Comparator for the issues added to cycle at date. |
| addedToCyclePeriod | CyclePeriodComparator | Comparator for the period when issue was added to a cycle. |
| dueDate | NullableTimelessDateComparator | Comparator for the issues due date. |
| accumulatedStateUpdatedAt | NullableDateComparator | [Internal] Comparator for the issue's accumulatedStateUpdatedAt date. |
| snoozedUntilAt | NullableDateComparator | Comparator for the issues snoozed until date. |
| assignee | NullableUserFilter | Filters that the issues assignee must satisfy. |
| delegate | NullableUserFilter | Filters that the issue's delegated agent must satisfy. |
| lastAppliedTemplate | NullableTemplateFilter | Filters that the last applied template must satisfy. |
| recurringIssueTemplate | NullableTemplateFilter | [ALPHA] Filters that the recurring issue template must satisfy. |
| sourceMetadata | SourceMetadataComparator | Filters that the source must satisfy. |
| creator | NullableUserFilter | Filters that the issues creator must satisfy. |
| parent | NullableIssueFilter | Filters that the issue parent must satisfy. |
| snoozedBy | NullableUserFilter | Filters that the issues snoozer must satisfy. |
| labels | IssueLabelCollectionFilter | Filters that issue labels must satisfy. |
| subscribers | UserCollectionFilter | Filters that issue subscribers must satisfy. |
| hasSharedUsers | RelationExistsComparator | Comparator for filtering issues which have been shared with users outside of the team. |
| sharedWith | UserCollectionFilter | Filters that users the issue has been shared with must satisfy. |
| team | TeamFilter | Filters that the issues team must satisfy. |
| projectMilestone | NullableProjectMilestoneFilter | Filters that the issues project milestone must satisfy. |
| comments | CommentCollectionFilter | Filters that the issues comments must satisfy. |
| activity | ActivityCollectionFilter | Filters that the issue's activities must satisfy. |
| suggestions | IssueSuggestionCollectionFilter | [Internal] Filters that the issue's suggestions must satisfy. |
| cycle | NullableCycleFilter | Filters that the issues cycle must satisfy. |
| project | NullableProjectFilter | Filters that the issues project must satisfy. |
| state | WorkflowStateFilter | Filters that the issues state must satisfy. |
| children | IssueCollectionFilter | Filters that the child issues must satisfy. |
| attachments | AttachmentCollectionFilter | Filters that the issues attachments must satisfy. |
| searchableContent | ContentComparator | [Internal] Comparator for the issues content. |
| hasRelatedRelations | RelationExistsComparator | Comparator for filtering issues with relations. |
| hasDuplicateRelations | RelationExistsComparator | Comparator for filtering issues which are duplicates. |
| hasBlockedByRelations | RelationExistsComparator | Comparator for filtering issues which are blocked. |
| hasBlockingRelations | RelationExistsComparator | Comparator for filtering issues which are blocking. |
| hasSuggestedRelatedIssues | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested related issues. |
| hasSuggestedSimilarIssues | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested similar issues. |
| hasSuggestedAssignees | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested assignees. |
| hasSuggestedProjects | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested projects. |
| hasSuggestedLabels | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested labels. |
| hasSuggestedTeams | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested teams. |
| slaStatus | SlaStatusComparator | Comparator for the issues sla status. |
| reactions | ReactionCollectionFilter | Filters that the issues reactions must satisfy. |
| needs | CustomerNeedCollectionFilter | Filters that the issue's customer needs must satisfy. |
| releases | ReleaseCollectionFilter | [ALPHA] Filters that the issue's releases must satisfy. |
| customerCount | NumberComparator | Count of customers |
| customerImportantCount | NumberComparator | Count of important customers |
| leadTime | NullableDurationComparator | [Internal] Lead time (created -> completed) comparator. |
| cycleTime | NullableDurationComparator | [Internal] Cycle time (started -> completed) comparator. |
| ageTime | NullableDurationComparator | [Internal] Age (created -> now) comparator, defined if the issue is still open. |
| triageTime | NullableDurationComparator | [Internal] Triage time (entered triaged -> triaged) comparator. |
| and | LIST | Compound filters, all of which need to be matched by the issue. |
| or | LIST | Compound filters, one of which need to be matched by the issue. |
| some | IssueFilter | Filters that needs to be matched by some issues. |
| every | IssueFilter | Filters that needs to be matched by all issues. |
| length | NumberComparator | Comparator for the collection length. |

## IssueCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| title | String | The title of the issue. |
| description | String | The issue description in markdown format. |
| descriptionData | JSON | [Internal] The issue description as a Prosemirror document. |
| assigneeId | String | The identifier of the user to assign the issue to. |
| delegateId | String | The identifier of the agent user to delegate the issue to. |
| parentId | String | The identifier of the parent issue. Can be a UUID or issue identifier (e.g., 'LIN-123'). |
| priority | Int | The priority of the issue. 0 = No priority, 1 = Urgent, 2 = High, 3 = Normal, 4 = Low. |
| estimate | Int | The estimated complexity of the issue. |
| subscriberIds | LIST | The identifiers of the users subscribing to this ticket. |
| labelIds | LIST | The identifiers of the issue labels associated with this ticket. |
| teamId | String | The identifier of the team associated with the issue. |
| cycleId | String | The cycle associated with the issue. |
| projectId | String | The project associated with the issue. |
| projectMilestoneId | String | The project milestone associated with the issue. |
| lastAppliedTemplateId | String | The ID of the last template applied to the issue. |
| stateId | String | The team state of the issue. |
| referenceCommentId | String | The comment the issue is referencing. |
| sourceCommentId | String | The comment the issue is created from. |
| sourcePullRequestCommentId | String | [Internal] The pull request comment the issue is created from. |
| sortOrder | Float | The position of the issue related to other issues. |
| prioritySortOrder | Float | The position of the issue related to other issues, when ordered by priority. |
| subIssueSortOrder | Float | The position of the issue in parent's sub-issue list. |
| dueDate | TimelessDate | The date at which the issue is due. |
| createAsUser | String | Create issue as a user with the provided name. This option is only available to OAuth applications creating issues in `actor=app` mode. |
| displayIconUrl | String | Provide an external user avatar URL. Can only be used in conjunction with the `createAsUser` options. This option is only available to OAuth applications creating comments in `actor=app` mode. |
| preserveSortOrderOnCreate | Boolean | Whether the passed sort order should be preserved. |
| createdAt | DateTime | The date when the issue was created (e.g. if importing from another system). Must be a date in the past. If none is provided, the backend will generate the time as now. |
| slaBreachesAt | DateTime | [Internal] The timestamp at which an issue will be considered in breach of SLA. |
| slaStartedAt | DateTime | [Internal] The timestamp at which the issue's SLA was started. |
| templateId | String | The identifier of a template the issue should be created from. If other values are provided in the input, they will override template values. |
| completedAt | DateTime | The date when the issue was completed (e.g. if importing from another system). Must be a date in the past and after createdAt date. Cannot be provided with an incompatible workflow state. |
| slaType | SLADayCountType | The SLA day count type for the issue. Whether SLA should be business days only or calendar days (default). |
| useDefaultTemplate | Boolean | Whether to use the default template for the team. When set to true, the default template of this team based on user's membership will be applied. |

## IssueFilter
Issue filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IssueIDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| number | NumberComparator | Comparator for the issues number. |
| title | StringComparator | Comparator for the issues title. |
| description | NullableStringComparator | Comparator for the issues description. |
| priority | NullableNumberComparator | Comparator for the issues priority. 0 = No priority, 1 = Urgent, 2 = High, 3 = Normal, 4 = Low. |
| estimate | EstimateComparator | Comparator for the issues estimate. |
| startedAt | NullableDateComparator | Comparator for the issues started at date. |
| triagedAt | NullableDateComparator | Comparator for the issues triaged at date. |
| completedAt | NullableDateComparator | Comparator for the issues completed at date. |
| canceledAt | NullableDateComparator | Comparator for the issues canceled at date. |
| archivedAt | NullableDateComparator | Comparator for the issues archived at date. |
| autoClosedAt | NullableDateComparator | Comparator for the issues auto closed at date. |
| autoArchivedAt | NullableDateComparator | Comparator for the issues auto archived at date. |
| addedToCycleAt | NullableDateComparator | Comparator for the issues added to cycle at date. |
| addedToCyclePeriod | CyclePeriodComparator | Comparator for the period when issue was added to a cycle. |
| dueDate | NullableTimelessDateComparator | Comparator for the issues due date. |
| accumulatedStateUpdatedAt | NullableDateComparator | [Internal] Comparator for the issue's accumulatedStateUpdatedAt date. |
| snoozedUntilAt | NullableDateComparator | Comparator for the issues snoozed until date. |
| assignee | NullableUserFilter | Filters that the issues assignee must satisfy. |
| delegate | NullableUserFilter | Filters that the issue's delegated agent must satisfy. |
| lastAppliedTemplate | NullableTemplateFilter | Filters that the last applied template must satisfy. |
| recurringIssueTemplate | NullableTemplateFilter | [ALPHA] Filters that the recurring issue template must satisfy. |
| sourceMetadata | SourceMetadataComparator | Filters that the source must satisfy. |
| creator | NullableUserFilter | Filters that the issues creator must satisfy. |
| parent | NullableIssueFilter | Filters that the issue parent must satisfy. |
| snoozedBy | NullableUserFilter | Filters that the issues snoozer must satisfy. |
| labels | IssueLabelCollectionFilter | Filters that issue labels must satisfy. |
| subscribers | UserCollectionFilter | Filters that issue subscribers must satisfy. |
| hasSharedUsers | RelationExistsComparator | Comparator for filtering issues which have been shared with users outside of the team. |
| sharedWith | UserCollectionFilter | Filters that users the issue has been shared with must satisfy. |
| team | TeamFilter | Filters that the issues team must satisfy. |
| projectMilestone | NullableProjectMilestoneFilter | Filters that the issues project milestone must satisfy. |
| comments | CommentCollectionFilter | Filters that the issues comments must satisfy. |
| activity | ActivityCollectionFilter | Filters that the issue's activities must satisfy. |
| suggestions | IssueSuggestionCollectionFilter | [Internal] Filters that the issue's suggestions must satisfy. |
| cycle | NullableCycleFilter | Filters that the issues cycle must satisfy. |
| project | NullableProjectFilter | Filters that the issues project must satisfy. |
| state | WorkflowStateFilter | Filters that the issues state must satisfy. |
| children | IssueCollectionFilter | Filters that the child issues must satisfy. |
| attachments | AttachmentCollectionFilter | Filters that the issues attachments must satisfy. |
| searchableContent | ContentComparator | [Internal] Comparator for the issues content. |
| hasRelatedRelations | RelationExistsComparator | Comparator for filtering issues with relations. |
| hasDuplicateRelations | RelationExistsComparator | Comparator for filtering issues which are duplicates. |
| hasBlockedByRelations | RelationExistsComparator | Comparator for filtering issues which are blocked. |
| hasBlockingRelations | RelationExistsComparator | Comparator for filtering issues which are blocking. |
| hasSuggestedRelatedIssues | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested related issues. |
| hasSuggestedSimilarIssues | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested similar issues. |
| hasSuggestedAssignees | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested assignees. |
| hasSuggestedProjects | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested projects. |
| hasSuggestedLabels | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested labels. |
| hasSuggestedTeams | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested teams. |
| slaStatus | SlaStatusComparator | Comparator for the issues sla status. |
| reactions | ReactionCollectionFilter | Filters that the issues reactions must satisfy. |
| needs | CustomerNeedCollectionFilter | Filters that the issue's customer needs must satisfy. |
| releases | ReleaseCollectionFilter | [ALPHA] Filters that the issue's releases must satisfy. |
| customerCount | NumberComparator | Count of customers |
| customerImportantCount | NumberComparator | Count of important customers |
| leadTime | NullableDurationComparator | [Internal] Lead time (created -> completed) comparator. |
| cycleTime | NullableDurationComparator | [Internal] Cycle time (started -> completed) comparator. |
| ageTime | NullableDurationComparator | [Internal] Age (created -> now) comparator, defined if the issue is still open. |
| triageTime | NullableDurationComparator | [Internal] Triage time (entered triaged -> triaged) comparator. |
| and | LIST | Compound filters, all of which need to be matched by the issue. |
| or | LIST | Compound filters, one of which need to be matched by the issue. |

## IssueIDComparator
Comparator for issue identifiers.

| Field | Type | Description |
|-------|------|-------------|
| eq | ID | Equals constraint. |
| neq | ID | Not-equals constraint. |
| in | LIST | In-array constraint. |
| nin | LIST | Not-in-array constraint. |

## IssueImportUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| mapping | JSONObject | The mapping configuration for the import. |

## IssueLabelCollectionFilter
Issue label filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| name | StringComparator | Comparator for the name. |
| isGroup | BooleanComparator | Comparator for whether the label is a group label. |
| creator | NullableUserFilter | Filters that the issue labels creator must satisfy. |
| team | NullableTeamFilter | Filters that the issue labels team must satisfy. |
| parent | IssueLabelFilter | Filters that the issue label's parent label must satisfy. |
| null | Boolean | Filter based on the existence of the relation. |
| and | LIST | Compound filters, all of which need to be matched by the label. |
| or | LIST | Compound filters, one of which need to be matched by the label. |
| some | IssueLabelFilter | Filters that needs to be matched by some issue labels. |
| every | IssueLabelFilter | Filters that needs to be matched by all issue labels. |
| length | NumberComparator | Comparator for the collection length. |

## IssueLabelCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| name | String | The name of the label. |
| description | String | The description of the label. |
| color | String | The color of the label. |
| parentId | String | The identifier of the parent label. |
| teamId | String | The team associated with the label. If not given, the label will be associated with the entire workspace. |
| isGroup | Boolean | Whether the label is a group. |
| retiredAt | DateTime | When the label was retired. |

## IssueLabelFilter
Issue label filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| name | StringComparator | Comparator for the name. |
| isGroup | BooleanComparator | Comparator for whether the label is a group label. |
| creator | NullableUserFilter | Filters that the issue labels creator must satisfy. |
| team | NullableTeamFilter | Filters that the issue labels team must satisfy. |
| parent | IssueLabelFilter | Filters that the issue label's parent label must satisfy. |
| and | LIST | Compound filters, all of which need to be matched by the label. |
| or | LIST | Compound filters, one of which need to be matched by the label. |

## IssueLabelUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| name | String | The name of the label. |
| description | String | The description of the label. |
| parentId | String | The identifier of the parent label. |
| color | String | The color of the label. |
| isGroup | Boolean | Whether the label is a group. |
| retiredAt | DateTime | When the label was retired. |

## IssueReferenceInput
A reference to an issue found during release creation.

| Field | Type | Description |
|-------|------|-------------|
| identifier | String | The issue identifier (e.g. ENG-123). |
| commitSha | String | The commit SHA where this issue reference was found. |

## IssueRelationCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| type | IssueRelationType | The type of relation of the issue to the related issue. |
| issueId | String | The identifier of the issue that is related to another issue. Can be a UUID or issue identifier (e.g., 'LIN-123'). |
| relatedIssueId | String | The identifier of the related issue. Can be a UUID or issue identifier (e.g., 'LIN-123'). |

## IssueRelationUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| type | String | The type of relation of the issue to the related issue. |
| issueId | String | The identifier of the issue that is related to another issue. Can be a UUID or issue identifier (e.g., 'LIN-123'). |
| relatedIssueId | String | The identifier of the related issue. Can be a UUID or issue identifier (e.g., 'LIN-123'). |

## IssueSortInput
Issue sorting options.

| Field | Type | Description |
|-------|------|-------------|
| priority | PrioritySort | Sort by priority |
| estimate | EstimateSort | Sort by estimate |
| title | TitleSort | Sort by issue title |
| label | LabelSort | Sort by label |
| labelGroup | LabelGroupSort | Sort by label group |
| slaStatus | SlaStatusSort | Sort by SLA status |
| createdAt | CreatedAtSort | Sort by issue creation date |
| updatedAt | UpdatedAtSort | Sort by issue update date |
| completedAt | CompletedAtSort | Sort by issue completion date |
| dueDate | DueDateSort | Sort by issue due date |
| accumulatedStateUpdatedAt | TimeInStatusSort | [Internal] Sort by the accumulated time in the current workflow state |
| cycle | CycleSort | Sort by Cycle start date |
| milestone | MilestoneSort | Sort by Project Milestone target date |
| assignee | AssigneeSort | Sort by assignee name |
| delegate | DelegateSort | Sort by delegate name |
| project | ProjectSort | Sort by Project name |
| team | TeamSort | Sort by Team name |
| manual | ManualSort | Sort by manual order |
| workflowState | WorkflowStateSort | Sort by workflow state type |
| customer | CustomerSort | Sort by customer name |
| customerRevenue | CustomerRevenueSort | Sort by customer revenue |
| customerCount | CustomerCountSort | Sort by number of customers associated with the issue |
| customerImportantCount | CustomerImportantCountSort | Sort by number of important customers associated with the issue |
| rootIssue | RootIssueSort | Sort by the root issue |
| linkCount | LinkCountSort | [ALPHA] Sort by number of links associated with the issue |

## IssueSuggestionCollectionFilter
IssueSuggestion collection filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| type | StringComparator | Comparator for the suggestion type. |
| state | StringComparator | Comparator for the suggestion state. |
| suggestedUser | NullableUserFilter | Filters that the suggested user must satisfy. |
| suggestedProject | NullableProjectFilter | Filters that the suggested project must satisfy. |
| suggestedTeam | NullableTeamFilter | Filters that the suggested team must satisfy. |
| suggestedLabel | IssueLabelFilter | Filters that the suggested label must satisfy. |
| and | LIST | Compound filters, all of which need to be matched by the suggestion. |
| or | LIST | Compound filters, one of which need to be matched by the suggestion. |
| some | IssueSuggestionFilter | Filters that needs to be matched by some suggestions. |
| every | IssueSuggestionFilter | Filters that needs to be matched by all suggestions. |
| length | NumberComparator | Comparator for the collection length. |

## IssueSuggestionFilter
IssueSuggestion filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| type | StringComparator | Comparator for the suggestion type. |
| state | StringComparator | Comparator for the suggestion state. |
| suggestedUser | NullableUserFilter | Filters that the suggested user must satisfy. |
| suggestedProject | NullableProjectFilter | Filters that the suggested project must satisfy. |
| suggestedTeam | NullableTeamFilter | Filters that the suggested team must satisfy. |
| suggestedLabel | IssueLabelFilter | Filters that the suggested label must satisfy. |
| and | LIST | Compound filters, all of which need to be matched by the suggestion. |
| or | LIST | Compound filters, one of which need to be matched by the suggestion. |

## IssueToReleaseCreateInput
[ALPHA] The properties of the issueToRelease to create.

| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| issueId | String | The identifier of the issue. Can be a UUID or issue identifier (e.g., 'LIN-123'). |
| releaseId | String | The identifier of the release |

## IssueUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| title | String | The issue title. |
| description | String | The issue description in markdown format. |
| descriptionData | JSON | [Internal] The issue description as a Prosemirror document. |
| assigneeId | String | The identifier of the user to assign the issue to. |
| delegateId | String | The identifier of the agent user to delegate the issue to. |
| parentId | String | The identifier of the parent issue. Can be a UUID or issue identifier (e.g., 'LIN-123'). |
| priority | Int | The priority of the issue. 0 = No priority, 1 = Urgent, 2 = High, 3 = Normal, 4 = Low. |
| estimate | Int | The estimated complexity of the issue. |
| subscriberIds | LIST | The identifiers of the users subscribing to this ticket. |
| labelIds | LIST | The identifiers of the issue labels associated with this ticket. |
| addedLabelIds | LIST | The identifiers of the issue labels to be added to this issue. |
| removedLabelIds | LIST | The identifiers of the issue labels to be removed from this issue. |
| teamId | String | The identifier of the team associated with the issue. |
| cycleId | String | The cycle associated with the issue. |
| projectId | String | The project associated with the issue. |
| projectMilestoneId | String | The project milestone associated with the issue. |
| lastAppliedTemplateId | String | The ID of the last template applied to the issue. |
| stateId | String | The team state of the issue. |
| sortOrder | Float | The position of the issue related to other issues. |
| prioritySortOrder | Float | The position of the issue related to other issues, when ordered by priority. |
| subIssueSortOrder | Float | The position of the issue in parent's sub-issue list. |
| dueDate | TimelessDate | The date at which the issue is due. |
| trashed | Boolean | Whether the issue has been trashed. |
| slaBreachesAt | DateTime | [Internal] The timestamp at which an issue will be considered in breach of SLA. |
| slaStartedAt | DateTime | [Internal] The timestamp at which the issue's SLA was started. |
| snoozedUntilAt | DateTime | The time until an issue will be snoozed in Triage view. |
| snoozedById | String | The identifier of the user who snoozed the issue. |
| slaType | SLADayCountType | The SLA day count type for the issue. Whether SLA should be business days only or calendar days (default). |
| autoClosedByParentClosing | Boolean | Whether the issue was automatically closed because its parent issue was closed. |

## JiraFetchProjectStatusesInput
| Field | Type | Description |
|-------|------|-------------|
| integrationId | String | The id of the Jira integration. |
| projectId | String | The Jira project ID to fetch statuses for. |

## JiraProjectDataInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The Jira id for this project. |
| key | String | The Jira key for this project, such as ENG. |
| name | String | The Jira name for this project, such as Engineering. |

## LabelGroupSort
Issue label-group sorting options.

| Field | Type | Description |
|-------|------|-------------|
| nulls | PaginationNulls | Whether nulls should be sorted first or last |
| order | PaginationSortOrder | The order for the individual sort |
| labelGroupId | String | The label-group id to sort by |

## LabelSort
Issue label sorting options.

| Field | Type | Description |
|-------|------|-------------|
| nulls | PaginationNulls | Whether nulls should be sorted first or last |
| order | PaginationSortOrder | The order for the individual sort |

## MicrosoftTeamsSettingsInput
| Field | Type | Description |
|-------|------|-------------|
| tenantName | String | The display name of the Azure AD tenant. |

## NullableCommentFilter
Comment filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| body | StringComparator | Comparator for the comment's body. |
| user | UserFilter | Filters that the comment's creator must satisfy. |
| issue | NullableIssueFilter | Filters that the comment's issue must satisfy. |
| projectUpdate | NullableProjectUpdateFilter | Filters that the comment's project update must satisfy. |
| parent | NullableCommentFilter | Filters that the comment parent must satisfy. |
| documentContent | NullableDocumentContentFilter | Filters that the comment's document content must satisfy. |
| reactions | ReactionCollectionFilter | Filters that the comment's reactions must satisfy. |
| needs | CustomerNeedCollectionFilter | Filters that the comment's customer needs must satisfy. |
| null | Boolean | Filter based on the existence of the relation. |
| and | LIST | Compound filters, all of which need to be matched by the comment. |
| or | LIST | Compound filters, one of which need to be matched by the comment. |

## NullableCycleFilter
Cycle filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| number | NumberComparator | Comparator for the cycle number. |
| name | StringComparator | Comparator for the cycle name. |
| startsAt | DateComparator | Comparator for the cycle start date. |
| endsAt | DateComparator | Comparator for the cycle ends at date. |
| completedAt | DateComparator | Comparator for the cycle completed at date. |
| isActive | BooleanComparator | Comparator for the filtering active cycle. |
| isInCooldown | BooleanComparator | Comparator for filtering for whether the cycle is currently in cooldown. |
| isNext | BooleanComparator | Comparator for the filtering next cycle. |
| isPrevious | BooleanComparator | Comparator for the filtering previous cycle. |
| isFuture | BooleanComparator | Comparator for the filtering future cycles. |
| isPast | BooleanComparator | Comparator for the filtering past cycles. |
| team | TeamFilter | Filters that the cycles team must satisfy. |
| issues | IssueCollectionFilter | Filters that the cycles issues must satisfy. |
| inheritedFromId | IDComparator | Comparator for the inherited cycle ID. |
| null | Boolean | Filter based on the existence of the relation. |
| and | LIST | Compound filters, all of which need to be matched by the cycle. |
| or | LIST | Compound filters, one of which need to be matched by the cycle. |

## NullableDocumentContentFilter
Document content filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| content | NullableStringComparator | Comparator for the document content. |
| project | ProjectFilter | Filters that the document content project must satisfy. |
| document | DocumentFilter | Filters that the document content document must satisfy. |
| null | Boolean | Filter based on the existence of the relation. |
| and | LIST | Compound filters, all of which need to be matched by the user. |
| or | LIST | Compound filters, one of which need to be matched by the user. |

## NullableIssueFilter
Issue filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IssueIDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| number | NumberComparator | Comparator for the issues number. |
| title | StringComparator | Comparator for the issues title. |
| description | NullableStringComparator | Comparator for the issues description. |
| priority | NullableNumberComparator | Comparator for the issues priority. 0 = No priority, 1 = Urgent, 2 = High, 3 = Normal, 4 = Low. |
| estimate | EstimateComparator | Comparator for the issues estimate. |
| startedAt | NullableDateComparator | Comparator for the issues started at date. |
| triagedAt | NullableDateComparator | Comparator for the issues triaged at date. |
| completedAt | NullableDateComparator | Comparator for the issues completed at date. |
| canceledAt | NullableDateComparator | Comparator for the issues canceled at date. |
| archivedAt | NullableDateComparator | Comparator for the issues archived at date. |
| autoClosedAt | NullableDateComparator | Comparator for the issues auto closed at date. |
| autoArchivedAt | NullableDateComparator | Comparator for the issues auto archived at date. |
| addedToCycleAt | NullableDateComparator | Comparator for the issues added to cycle at date. |
| addedToCyclePeriod | CyclePeriodComparator | Comparator for the period when issue was added to a cycle. |
| dueDate | NullableTimelessDateComparator | Comparator for the issues due date. |
| accumulatedStateUpdatedAt | NullableDateComparator | [Internal] Comparator for the issue's accumulatedStateUpdatedAt date. |
| snoozedUntilAt | NullableDateComparator | Comparator for the issues snoozed until date. |
| assignee | NullableUserFilter | Filters that the issues assignee must satisfy. |
| delegate | NullableUserFilter | Filters that the issue's delegated agent must satisfy. |
| lastAppliedTemplate | NullableTemplateFilter | Filters that the last applied template must satisfy. |
| recurringIssueTemplate | NullableTemplateFilter | [ALPHA] Filters that the recurring issue template must satisfy. |
| sourceMetadata | SourceMetadataComparator | Filters that the source must satisfy. |
| creator | NullableUserFilter | Filters that the issues creator must satisfy. |
| parent | NullableIssueFilter | Filters that the issue parent must satisfy. |
| snoozedBy | NullableUserFilter | Filters that the issues snoozer must satisfy. |
| labels | IssueLabelCollectionFilter | Filters that issue labels must satisfy. |
| subscribers | UserCollectionFilter | Filters that issue subscribers must satisfy. |
| hasSharedUsers | RelationExistsComparator | Comparator for filtering issues which have been shared with users outside of the team. |
| sharedWith | UserCollectionFilter | Filters that users the issue has been shared with must satisfy. |
| team | TeamFilter | Filters that the issues team must satisfy. |
| projectMilestone | NullableProjectMilestoneFilter | Filters that the issues project milestone must satisfy. |
| comments | CommentCollectionFilter | Filters that the issues comments must satisfy. |
| activity | ActivityCollectionFilter | Filters that the issue's activities must satisfy. |
| suggestions | IssueSuggestionCollectionFilter | [Internal] Filters that the issue's suggestions must satisfy. |
| cycle | NullableCycleFilter | Filters that the issues cycle must satisfy. |
| project | NullableProjectFilter | Filters that the issues project must satisfy. |
| state | WorkflowStateFilter | Filters that the issues state must satisfy. |
| children | IssueCollectionFilter | Filters that the child issues must satisfy. |
| attachments | AttachmentCollectionFilter | Filters that the issues attachments must satisfy. |
| searchableContent | ContentComparator | [Internal] Comparator for the issues content. |
| hasRelatedRelations | RelationExistsComparator | Comparator for filtering issues with relations. |
| hasDuplicateRelations | RelationExistsComparator | Comparator for filtering issues which are duplicates. |
| hasBlockedByRelations | RelationExistsComparator | Comparator for filtering issues which are blocked. |
| hasBlockingRelations | RelationExistsComparator | Comparator for filtering issues which are blocking. |
| hasSuggestedRelatedIssues | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested related issues. |
| hasSuggestedSimilarIssues | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested similar issues. |
| hasSuggestedAssignees | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested assignees. |
| hasSuggestedProjects | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested projects. |
| hasSuggestedLabels | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested labels. |
| hasSuggestedTeams | RelationExistsComparator | [Internal] Comparator for filtering issues which have suggested teams. |
| slaStatus | SlaStatusComparator | Comparator for the issues sla status. |
| reactions | ReactionCollectionFilter | Filters that the issues reactions must satisfy. |
| needs | CustomerNeedCollectionFilter | Filters that the issue's customer needs must satisfy. |
| releases | ReleaseCollectionFilter | [ALPHA] Filters that the issue's releases must satisfy. |
| customerCount | NumberComparator | Count of customers |
| customerImportantCount | NumberComparator | Count of important customers |
| leadTime | NullableDurationComparator | [Internal] Lead time (created -> completed) comparator. |
| cycleTime | NullableDurationComparator | [Internal] Cycle time (started -> completed) comparator. |
| ageTime | NullableDurationComparator | [Internal] Age (created -> now) comparator, defined if the issue is still open. |
| triageTime | NullableDurationComparator | [Internal] Triage time (entered triaged -> triaged) comparator. |
| null | Boolean | Filter based on the existence of the relation. |
| and | LIST | Compound filters, all of which need to be matched by the issue. |
| or | LIST | Compound filters, one of which need to be matched by the issue. |

## NullableProjectFilter
Project filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| name | StringComparator | Comparator for the project name. |
| slugId | StringComparator | Comparator for the project slug ID. |
| state | StringComparator | [DEPRECATED] Comparator for the project state. |
| status | ProjectStatusFilter | Filters that the project's status must satisfy. |
| priority | NullableNumberComparator | Comparator for the projects priority. |
| labels | ProjectLabelCollectionFilter | Filters that project labels must satisfy. |
| searchableContent | ContentComparator | [Internal] Comparator for the project's content. |
| startedAt | NullableDateComparator | Comparator for the project started date (when it was moved to an "In Progress" status). |
| completedAt | NullableDateComparator | Comparator for the project completion date. |
| canceledAt | NullableDateComparator | Comparator for the project cancelation date. |
| startDate | NullableDateComparator | Comparator for the project start date. |
| targetDate | NullableDateComparator | Comparator for the project target date. |
| health | StringComparator | Comparator for the project health: onTrack, atRisk, offTrack |
| healthWithAge | StringComparator | Comparator for the project health (with age): onTrack, atRisk, offTrack, outdated, noUpdate |
| activityType | StringComparator | [ALPHA] Comparator for the project activity type: buzzin, active, some, none |
| hasRelatedRelations | RelationExistsComparator | Comparator for filtering projects with relations. |
| hasDependedOnByRelations | RelationExistsComparator | [Deprecated] Comparator for filtering projects which this is depended on by. |
| hasDependsOnRelations | RelationExistsComparator | [Deprecated]Comparator for filtering projects which this depends on. |
| hasBlockedByRelations | RelationExistsComparator | Comparator for filtering projects which are blocked. |
| hasBlockingRelations | RelationExistsComparator | Comparator for filtering projects which are blocking. |
| hasViolatedRelations | RelationExistsComparator | Comparator for filtering projects with violated dependencies. |
| projectUpdates | ProjectUpdatesCollectionFilter | Comparator for the project updates. |
| creator | UserFilter | Filters that the projects creator must satisfy. |
| lead | NullableUserFilter | Filters that the projects lead must satisfy. |
| members | UserCollectionFilter | Filters that the projects members must satisfy. |
| issues | IssueCollectionFilter | Filters that the projects issues must satisfy. |
| roadmaps | RoadmapCollectionFilter | Filters that the projects roadmaps must satisfy. |
| initiatives | InitiativeCollectionFilter | Filters that the projects initiatives must satisfy. |
| projectMilestones | ProjectMilestoneCollectionFilter | Filters that the project's milestones must satisfy. |
| completedProjectMilestones | ProjectMilestoneCollectionFilter | Filters that the project's completed milestones must satisfy. |
| nextProjectMilestone | ProjectMilestoneFilter | Filters that the project's next milestone must satisfy. |
| accessibleTeams | TeamCollectionFilter | Filters that the project's team must satisfy. |
| lastAppliedTemplate | NullableTemplateFilter | Filters that the last applied template must satisfy. |
| needs | CustomerNeedCollectionFilter | Filters that the project's customer needs must satisfy. |
| customerCount | NumberComparator | Count of customers |
| customerImportantCount | NumberComparator | Count of important customers |
| null | Boolean | Filter based on the existence of the relation. |
| and | LIST | Compound filters, all of which need to be matched by the project. |
| or | LIST | Compound filters, one of which need to be matched by the project. |

## NullableProjectMilestoneFilter
Project milestone filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| name | NullableStringComparator | Comparator for the project milestone name. |
| targetDate | NullableDateComparator | Comparator for the project milestone target date. |
| project | NullableProjectFilter | Filters that the project milestone's project must satisfy. |
| null | Boolean | Filter based on the existence of the relation. |
| and | LIST | Compound filters, all of which need to be matched by the project milestone. |
| or | LIST | Compound filters, one of which need to be matched by the project milestone. |

## NullableProjectUpdateFilter
Nullable project update filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| user | UserFilter | Filters that the project update creator must satisfy. |
| project | ProjectFilter | Filters that the project update project must satisfy. |
| reactions | ReactionCollectionFilter | Filters that the project updates reactions must satisfy. |
| null | Boolean | Filter based on the existence of the relation. |
| and | LIST | Compound filters, all of which need to be matched by the project update. |
| or | LIST | Compound filters, one of which need to be matched by the project update. |

## NullableTeamFilter
Team filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| name | StringComparator | Comparator for the team name. |
| key | StringComparator | Comparator for the team key. |
| description | NullableStringComparator | Comparator for the team description. |
| private | BooleanComparator | Comparator for the team privacy. |
| issues | IssueCollectionFilter | Filters that the teams issues must satisfy. |
| parent | NullableTeamFilter | Filters that the teams parent must satisfy. |
| null | Boolean | Filter based on the existence of the relation. |
| and | LIST | Compound filters, all of which need to be matched by the team. |
| or | LIST | Compound filters, one of which need to be matched by the team. |

## ProjectCollectionFilter
Project filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| name | StringComparator | Comparator for the project name. |
| slugId | StringComparator | Comparator for the project slug ID. |
| state | StringComparator | [DEPRECATED] Comparator for the project state. |
| status | ProjectStatusFilter | Filters that the project's status must satisfy. |
| priority | NullableNumberComparator | Comparator for the projects priority. |
| labels | ProjectLabelCollectionFilter | Filters that project labels must satisfy. |
| searchableContent | ContentComparator | [Internal] Comparator for the project's content. |
| startedAt | NullableDateComparator | Comparator for the project started date (when it was moved to an "In Progress" status). |
| completedAt | NullableDateComparator | Comparator for the project completion date. |
| canceledAt | NullableDateComparator | Comparator for the project cancelation date. |
| startDate | NullableDateComparator | Comparator for the project start date. |
| targetDate | NullableDateComparator | Comparator for the project target date. |
| health | StringComparator | Comparator for the project health: onTrack, atRisk, offTrack |
| healthWithAge | StringComparator | Comparator for the project health (with age): onTrack, atRisk, offTrack, outdated, noUpdate |
| activityType | StringComparator | [ALPHA] Comparator for the project activity type: buzzin, active, some, none |
| hasRelatedRelations | RelationExistsComparator | Comparator for filtering projects with relations. |
| hasDependedOnByRelations | RelationExistsComparator | [Deprecated] Comparator for filtering projects which this is depended on by. |
| hasDependsOnRelations | RelationExistsComparator | [Deprecated]Comparator for filtering projects which this depends on. |
| hasBlockedByRelations | RelationExistsComparator | Comparator for filtering projects which are blocked. |
| hasBlockingRelations | RelationExistsComparator | Comparator for filtering projects which are blocking. |
| hasViolatedRelations | RelationExistsComparator | Comparator for filtering projects with violated dependencies. |
| projectUpdates | ProjectUpdatesCollectionFilter | Comparator for the project updates. |
| creator | UserFilter | Filters that the projects creator must satisfy. |
| lead | NullableUserFilter | Filters that the projects lead must satisfy. |
| members | UserCollectionFilter | Filters that the projects members must satisfy. |
| issues | IssueCollectionFilter | Filters that the projects issues must satisfy. |
| roadmaps | RoadmapCollectionFilter | Filters that the projects roadmaps must satisfy. |
| initiatives | InitiativeCollectionFilter | Filters that the projects initiatives must satisfy. |
| projectMilestones | ProjectMilestoneCollectionFilter | Filters that the project's milestones must satisfy. |
| completedProjectMilestones | ProjectMilestoneCollectionFilter | Filters that the project's completed milestones must satisfy. |
| nextProjectMilestone | ProjectMilestoneFilter | Filters that the project's next milestone must satisfy. |
| accessibleTeams | TeamCollectionFilter | Filters that the project's team must satisfy. |
| lastAppliedTemplate | NullableTemplateFilter | Filters that the last applied template must satisfy. |
| needs | CustomerNeedCollectionFilter | Filters that the project's customer needs must satisfy. |
| customerCount | NumberComparator | Count of customers |
| customerImportantCount | NumberComparator | Count of important customers |
| and | LIST | Compound filters, all of which need to be matched by the project. |
| or | LIST | Compound filters, one of which need to be matched by the project. |
| some | ProjectFilter | Filters that needs to be matched by some projects. |
| every | ProjectFilter | Filters that needs to be matched by all projects. |
| length | NumberComparator | Comparator for the collection length. |

## ProjectCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| name | String | The name of the project. |
| icon | String | The icon of the project. |
| color | String | The color of the project. |
| statusId | String | The ID of the project status. |
| description | String | The description for the project. |
| content | String | The project content as markdown. |
| teamIds | NON_NULL | The identifiers of the teams this project is associated with. |
| convertedFromIssueId | String | The ID of the issue from which that project is created. |
| lastAppliedTemplateId | String | The ID of the last template applied to the project. |
| templateId | String | The ID of the template to apply when creating the project. |
| useDefaultTemplate | Boolean | When set to true, the default project template of the first team provided will be applied. If templateId is provided, this will be ignored. |
| leadId | String | The identifier of the project lead. |
| memberIds | LIST | The identifiers of the members of this project. |
| startDate | TimelessDate | The planned start date of the project. |
| startDateResolution | DateResolutionType | The resolution of the project's start date. |
| targetDate | TimelessDate | The planned target date of the project. |
| targetDateResolution | DateResolutionType | The resolution of the project's estimated completion date. |
| sortOrder | Float | The sort order for the project within shared views. |
| prioritySortOrder | Float | The sort order for the project within shared views, when ordered by priority. |
| priority | Int | The priority of the project. 0 = No priority, 1 = Urgent, 2 = High, 3 = Normal, 4 = Low. |
| labelIds | LIST | [Internal]The identifiers of the project labels associated with this project. |

## ProjectCreatedAtSort
Project creation date sorting options.

| Field | Type | Description |
|-------|------|-------------|
| nulls | PaginationNulls | Whether nulls should be sorted first or last |
| order | PaginationSortOrder | The order for the individual sort |

## ProjectFilter
Project filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| name | StringComparator | Comparator for the project name. |
| slugId | StringComparator | Comparator for the project slug ID. |
| state | StringComparator | [DEPRECATED] Comparator for the project state. |
| status | ProjectStatusFilter | Filters that the project's status must satisfy. |
| priority | NullableNumberComparator | Comparator for the projects priority. |
| labels | ProjectLabelCollectionFilter | Filters that project labels must satisfy. |
| searchableContent | ContentComparator | [Internal] Comparator for the project's content. |
| startedAt | NullableDateComparator | Comparator for the project started date (when it was moved to an "In Progress" status). |
| completedAt | NullableDateComparator | Comparator for the project completion date. |
| canceledAt | NullableDateComparator | Comparator for the project cancelation date. |
| startDate | NullableDateComparator | Comparator for the project start date. |
| targetDate | NullableDateComparator | Comparator for the project target date. |
| health | StringComparator | Comparator for the project health: onTrack, atRisk, offTrack |
| healthWithAge | StringComparator | Comparator for the project health (with age): onTrack, atRisk, offTrack, outdated, noUpdate |
| activityType | StringComparator | [ALPHA] Comparator for the project activity type: buzzin, active, some, none |
| hasRelatedRelations | RelationExistsComparator | Comparator for filtering projects with relations. |
| hasDependedOnByRelations | RelationExistsComparator | [Deprecated] Comparator for filtering projects which this is depended on by. |
| hasDependsOnRelations | RelationExistsComparator | [Deprecated]Comparator for filtering projects which this depends on. |
| hasBlockedByRelations | RelationExistsComparator | Comparator for filtering projects which are blocked. |
| hasBlockingRelations | RelationExistsComparator | Comparator for filtering projects which are blocking. |
| hasViolatedRelations | RelationExistsComparator | Comparator for filtering projects with violated dependencies. |
| projectUpdates | ProjectUpdatesCollectionFilter | Comparator for the project updates. |
| creator | UserFilter | Filters that the projects creator must satisfy. |
| lead | NullableUserFilter | Filters that the projects lead must satisfy. |
| members | UserCollectionFilter | Filters that the projects members must satisfy. |
| issues | IssueCollectionFilter | Filters that the projects issues must satisfy. |
| roadmaps | RoadmapCollectionFilter | Filters that the projects roadmaps must satisfy. |
| initiatives | InitiativeCollectionFilter | Filters that the projects initiatives must satisfy. |
| projectMilestones | ProjectMilestoneCollectionFilter | Filters that the project's milestones must satisfy. |
| completedProjectMilestones | ProjectMilestoneCollectionFilter | Filters that the project's completed milestones must satisfy. |
| nextProjectMilestone | ProjectMilestoneFilter | Filters that the project's next milestone must satisfy. |
| accessibleTeams | TeamCollectionFilter | Filters that the project's team must satisfy. |
| lastAppliedTemplate | NullableTemplateFilter | Filters that the last applied template must satisfy. |
| needs | CustomerNeedCollectionFilter | Filters that the project's customer needs must satisfy. |
| customerCount | NumberComparator | Count of customers |
| customerImportantCount | NumberComparator | Count of important customers |
| and | LIST | Compound filters, all of which need to be matched by the project. |
| or | LIST | Compound filters, one of which need to be matched by the project. |

## ProjectHealthSort
Project health sorting options.

| Field | Type | Description |
|-------|------|-------------|
| nulls | PaginationNulls | Whether nulls should be sorted first or last |
| order | PaginationSortOrder | The order for the individual sort |

## ProjectLabelCollectionFilter
Project label filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| name | StringComparator | Comparator for the name. |
| isGroup | BooleanComparator | Comparator for whether the label is a group label. |
| creator | NullableUserFilter | Filters that the project labels creator must satisfy. |
| parent | ProjectLabelFilter | Filters that the project label's parent label must satisfy. |
| null | Boolean | Filter based on the existence of the relation. |
| and | LIST | Compound filters, all of which need to be matched by the label. |
| or | LIST | Compound filters, one of which need to be matched by the label. |
| some | ProjectLabelCollectionFilter | Filters that needs to be matched by some project labels. |
| every | ProjectLabelFilter | Filters that needs to be matched by all project labels. |
| length | NumberComparator | Comparator for the collection length. |

## ProjectLabelCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| name | String | The name of the label. |
| description | String | The description of the label. |
| color | String | The color of the label. |
| parentId | String | The identifier of the parent label. |
| isGroup | Boolean | Whether the label is a group. |
| retiredAt | DateTime | When the label was retired. |

## ProjectLabelFilter
Project label filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| name | StringComparator | Comparator for the name. |
| isGroup | BooleanComparator | Comparator for whether the label is a group label. |
| creator | NullableUserFilter | Filters that the project labels creator must satisfy. |
| parent | ProjectLabelFilter | Filters that the project label's parent label must satisfy. |
| and | LIST | Compound filters, all of which need to be matched by the label. |
| or | LIST | Compound filters, one of which need to be matched by the label. |

## ProjectLabelUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| name | String | The name of the label. |
| description | String | The description of the label. |
| parentId | String | The identifier of the parent label. |
| color | String | The color of the label. |
| isGroup | Boolean | Whether the label is a group. |
| retiredAt | DateTime | When the label was retired. |

## ProjectLeadSort
Project lead sorting options.

| Field | Type | Description |
|-------|------|-------------|
| nulls | PaginationNulls | Whether nulls should be sorted first or last |
| order | PaginationSortOrder | The order for the individual sort |

## ProjectManualSort
Project manual order sorting options.

| Field | Type | Description |
|-------|------|-------------|
| nulls | PaginationNulls | Whether nulls should be sorted first or last |
| order | PaginationSortOrder | The order for the individual sort |

## ProjectMilestoneCollectionFilter
Milestone collection filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| name | NullableStringComparator | Comparator for the project milestone name. |
| targetDate | NullableDateComparator | Comparator for the project milestone target date. |
| project | NullableProjectFilter | Filters that the project milestone's project must satisfy. |
| and | LIST | Compound filters, all of which need to be matched by the milestone. |
| or | LIST | Compound filters, one of which need to be matched by the milestone. |
| some | ProjectMilestoneFilter | Filters that needs to be matched by some milestones. |
| every | ProjectMilestoneFilter | Filters that needs to be matched by all milestones. |
| length | NumberComparator | Comparator for the collection length. |

## ProjectMilestoneCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| name | String | The name of the project milestone. |
| description | String | The description of the project milestone in markdown format. |
| descriptionData | JSONObject | [Internal] The description of the project milestone as a Prosemirror document. |
| targetDate | TimelessDate | The planned target date of the project milestone. |
| projectId | String | Related project for the project milestone. |
| sortOrder | Float | The sort order for the project milestone within a project. |

## ProjectMilestoneFilter
Project milestone filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| name | NullableStringComparator | Comparator for the project milestone name. |
| targetDate | NullableDateComparator | Comparator for the project milestone target date. |
| project | NullableProjectFilter | Filters that the project milestone's project must satisfy. |
| and | LIST | Compound filters, all of which need to be matched by the project milestone. |
| or | LIST | Compound filters, one of which need to be matched by the project milestone. |

## ProjectMilestoneMoveInput
| Field | Type | Description |
|-------|------|-------------|
| projectId | String | The identifier of the project to move the milestone to. |
| newIssueTeamId | String | The team id to move the attached issues to. This is needed when there is a mismatch between a project's teams and the milestone's issues' teams. Either this or addIssueTeamToProject is required in that situation to resolve constraints. |
| addIssueTeamToProject | Boolean | Whether to add each milestone issue's team to the project. This is needed when there is a mismatch between a project's teams and the milestone's issues' teams. Either this or newIssueTeamId is required in that situation to resolve constraints. |
| undoIssueTeamIds | LIST | A list of issue id to team ids, used for undoing a previous milestone move where the specified issues were moved from the specified teams. |
| undoProjectTeamIds | ProjectMilestoneMoveProjectTeamsInput | A mapping of project id to a previous set of team ids, used for undoing a previous milestone move where the specified teams were added to the project. |

## ProjectMilestoneMoveIssueToTeamInput
[Internal] Used for ProjectMilestoneMoveInput to describe a mapping between an issue and its team.

| Field | Type | Description |
|-------|------|-------------|
| issueId | String | The issue id in this relationship, you can use * as wildcard if all issues are being moved to the same team |
| teamId | String | The team id in this relationship |

## ProjectMilestoneMoveProjectTeamsInput
[Internal] Used for ProjectMilestoneMoveInput to describe a snapshot of a project and its team ids

| Field | Type | Description |
|-------|------|-------------|
| projectId | String | The project id |
| teamIds | NON_NULL | The team ids for the project |

## ProjectMilestoneUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| name | String | The name of the project milestone. |
| description | String | The description of the project milestone in markdown format. |
| descriptionData | JSONObject | [Internal] The description of the project milestone as a Prosemirror document. |
| targetDate | TimelessDate | The planned target date of the project milestone. |
| sortOrder | Float | The sort order for the project milestone within a project. |
| projectId | String | Related project for the project milestone. |

## ProjectNameSort
Project name sorting options.

| Field | Type | Description |
|-------|------|-------------|
| nulls | PaginationNulls | Whether nulls should be sorted first or last |
| order | PaginationSortOrder | The order for the individual sort |

## ProjectPrioritySort
Project priority sorting options.

| Field | Type | Description |
|-------|------|-------------|
| nulls | PaginationNulls | Whether nulls should be sorted first or last |
| order | PaginationSortOrder | The order for the individual sort |
| noPriorityFirst | Boolean | Whether to consider no priority as the highest or lowest priority |

## ProjectRelationCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| type | String | The type of relation of the project to the related project. |
| projectId | String | The identifier of the project that is related to another project. |
| projectMilestoneId | String | The identifier of the project milestone. |
| anchorType | String | The type of the anchor for the project. |
| relatedProjectId | String | The identifier of the related project. |
| relatedProjectMilestoneId | String | The identifier of the related project milestone. |
| relatedAnchorType | String | The type of the anchor for the related project. |

## ProjectRelationUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| type | String | The type of relation of the project to the related project. |
| projectId | String | The identifier of the project that is related to another project. |
| projectMilestoneId | String | The identifier of the project milestone. |
| anchorType | String | The type of the anchor for the project. |
| relatedProjectId | String | The identifier of the related project. |
| relatedProjectMilestoneId | String | The identifier of the related project milestone. |
| relatedAnchorType | String | The type of the anchor for the related project. |

## ProjectSort
Issue project sorting options.

| Field | Type | Description |
|-------|------|-------------|
| nulls | PaginationNulls | Whether nulls should be sorted first or last |
| order | PaginationSortOrder | The order for the individual sort |

## ProjectSortInput
Project sorting options.

| Field | Type | Description |
|-------|------|-------------|
| name | ProjectNameSort | Sort by project name |
| status | ProjectStatusSort | Sort by project status |
| priority | ProjectPrioritySort | Sort by project priority |
| manual | ProjectManualSort | Sort by manual order |
| targetDate | TargetDateSort | Sort by project target date |
| startDate | StartDateSort | Sort by project start date |
| createdAt | ProjectCreatedAtSort | Sort by project creation date |
| updatedAt | ProjectUpdatedAtSort | Sort by project update date |
| health | ProjectHealthSort | Sort by project health status. |
| lead | ProjectLeadSort | Sort by project lead name. |

## ProjectStatusCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| name | String | The name of the status. |
| color | String | The UI color of the status as a HEX string. |
| description | String | Description of the status. |
| position | Float | The position of the status in the workspace's project flow. |
| type | ProjectStatusType | The type of the project status. |
| indefinite | Boolean | Whether or not a project can be in this status indefinitely. |

## ProjectStatusFilter
Project status filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| name | StringComparator | Comparator for the project status name. |
| description | StringComparator | Comparator for the project status description. |
| position | NumberComparator | Comparator for the project status position. |
| type | StringComparator | Comparator for the project status type. |
| projects | ProjectCollectionFilter | Filters that the project status projects must satisfy. |
| and | LIST | Compound filters, all of which need to be matched by the project status. |
| or | LIST | Compound filters, one of which needs to be matched by the project status. |

## ProjectStatusSort
Project status sorting options.

| Field | Type | Description |
|-------|------|-------------|
| nulls | PaginationNulls | Whether nulls should be sorted first or last |
| order | PaginationSortOrder | The order for the individual sort |

## ProjectStatusUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| name | String | The name of the status. |
| color | String | The UI color of the status as a HEX string. |
| description | String | Description of the status. |
| position | Float | The position of the status in the workspace's project flow. |
| type | ProjectStatusType | The type of the project status. |
| indefinite | Boolean | Whether or not a project can be in this status indefinitely. |

## ProjectUpdateCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier. If none is provided, the backend will generate one. |
| body | String | The content of the project update in markdown format. |
| bodyData | JSON | [Internal] The content of the project update as a Prosemirror document. |
| projectId | String | The project to associate the project update with. |
| health | ProjectUpdateHealthType | The health of the project at the time of the update. |
| isDiffHidden | Boolean | Whether the diff between the current update and the previous one should be hidden. |

## ProjectUpdateFilter
Options for filtering project updates.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| user | UserFilter | Filters that the project update creator must satisfy. |
| project | ProjectFilter | Filters that the project update project must satisfy. |
| reactions | ReactionCollectionFilter | Filters that the project updates reactions must satisfy. |
| and | LIST | Compound filters, all of which need to be matched by the ProjectUpdate. |
| or | LIST | Compound filters, one of which need to be matched by the ProjectUpdate. |

## ProjectUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| statusId | String | The ID of the project status. |
| name | String | The name of the project. |
| description | String | The description for the project. |
| content | String | The project content as markdown. |
| convertedFromIssueId | String | The ID of the issue from which that project is created. |
| lastAppliedTemplateId | String | The ID of the last template applied to the project. |
| icon | String | The icon of the project. |
| color | String | The color of the project. |
| teamIds | LIST | The identifiers of the teams this project is associated with. |
| projectUpdateRemindersPausedUntilAt | DateTime | The time until which project update reminders are paused. |
| updateReminderFrequencyInWeeks | Float | The n-weekly frequency at which to prompt for updates. When not set, reminders are inherited from workspace. |
| updateReminderFrequency | Float | The frequency at which to prompt for updates. When not set, reminders are inherited from workspace. |
| frequencyResolution | FrequencyResolutionType | The frequency resolution. |
| updateRemindersDay | Day | The day at which to prompt for updates. |
| updateRemindersHour | Int | The hour at which to prompt for updates. |
| leadId | String | The identifier of the project lead. |
| memberIds | LIST | The identifiers of the members of this project. |
| startDate | TimelessDate | The planned start date of the project. |
| startDateResolution | DateResolutionType | The resolution of the project's start date. |
| targetDate | TimelessDate | The planned target date of the project. |
| targetDateResolution | DateResolutionType | The resolution of the project's estimated completion date. |
| completedAt | DateTime | The date when the project was completed. |
| canceledAt | DateTime | The date when the project was canceled. |
| slackNewIssue | Boolean | Whether to send new issue notifications to Slack. |
| slackIssueComments | Boolean | Whether to send new issue comment notifications to Slack. |
| slackIssueStatuses | Boolean | Whether to send issue status update notifications to Slack. |
| sortOrder | Float | The sort order for the project in shared views. |
| prioritySortOrder | Float | The sort order for the project within shared views, when ordered by priority. |
| trashed | Boolean | Whether the project has been trashed. |
| priority | Int | The priority of the project. 0 = No priority, 1 = Urgent, 2 = High, 3 = Normal, 4 = Low. |
| labelIds | LIST | The identifiers of the project labels associated with this project. |

## ProjectUpdateUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| body | String | The content of the project update in markdown format. |
| bodyData | JSON | The content of the project update as a Prosemirror document. |
| health | ProjectUpdateHealthType | The health of the project at the time of the update. |
| isDiffHidden | Boolean | Whether the diff between the current update and the previous one should be hidden. |

## ProjectUpdatedAtSort
Project update date sorting options.

| Field | Type | Description |
|-------|------|-------------|
| nulls | PaginationNulls | Whether nulls should be sorted first or last |
| order | PaginationSortOrder | The order for the individual sort |

## ProjectUpdatesCollectionFilter
Collection filtering options for filtering projects by project updates.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| health | StringComparator | Comparator for the project update health. |
| and | LIST | Compound filters, all of which need to be matched by the project update. |
| or | LIST | Compound filters, one of which need to be matched by the update. |
| some | ProjectUpdatesFilter | Filters that needs to be matched by some updates. |
| every | ProjectUpdatesFilter | Filters that needs to be matched by all updates. |
| length | NumberComparator | Comparator for the collection length. |

## ProjectUpdatesFilter
Options for filtering projects by project updates.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| health | StringComparator | Comparator for the project update health. |
| and | LIST | Compound filters, all of which need to be matched by the project updates. |
| or | LIST | Compound filters, one of which need to be matched by the project updates. |

## RoadmapCollectionFilter
Roadmap collection filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| name | StringComparator | Comparator for the roadmap name. |
| slugId | StringComparator | Comparator for the roadmap slug ID. |
| creator | UserFilter | Filters that the roadmap creator must satisfy. |
| and | LIST | Compound filters, all of which need to be matched by the roadmap. |
| or | LIST | Compound filters, one of which need to be matched by the roadmap. |
| some | RoadmapFilter | Filters that needs to be matched by some roadmaps. |
| every | RoadmapFilter | Filters that needs to be matched by all roadmaps. |
| length | NumberComparator | Comparator for the collection length. |

## RoadmapCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| name | String | The name of the roadmap. |
| description | String | The description of the roadmap. |
| ownerId | String | The owner of the roadmap. |
| sortOrder | Float | The sort order of the roadmap within the organization. |
| color | String | The roadmap's color. |

## RoadmapFilter
Roadmap filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| name | StringComparator | Comparator for the roadmap name. |
| slugId | StringComparator | Comparator for the roadmap slug ID. |
| creator | UserFilter | Filters that the roadmap creator must satisfy. |
| and | LIST | Compound filters, all of which need to be matched by the roadmap. |
| or | LIST | Compound filters, one of which need to be matched by the roadmap. |

## RoadmapToProjectCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| projectId | String | The identifier of the project. |
| roadmapId | String | The identifier of the roadmap. |
| sortOrder | Float | The sort order for the project within its organization. |

## RoadmapToProjectUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| sortOrder | Float | The sort order for the project within its organization. |

## RoadmapUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| name | String | The name of the roadmap. |
| description | String | The description of the roadmap. |
| ownerId | String | The owner of the roadmap. |
| sortOrder | Float | The sort order of the roadmap within the organization. |
| color | String | The roadmap's color. |

## RootIssueSort
Issue root-issue sorting options.

| Field | Type | Description |
|-------|------|-------------|
| nulls | PaginationNulls | Whether nulls should be sorted first or last |
| order | PaginationSortOrder | The order for the individual sort |
| sort | IssueSortInput | The sort to apply to the root issues |

## SlackAsksTeamSettingsInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The Linear team ID. |
| hasDefaultAsk | Boolean | Whether the default Asks template is enabled in the given channel for this team. |

## TeamCollectionFilter
Team collection filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| and | LIST | Compound filters, all of which need to be matched by the team. |
| or | LIST | Compound filters, one of which need to be matched by the team. |
| some | TeamFilter | Filters that needs to be matched by some teams. |
| every | TeamFilter | Filters that needs to be matched by all teams. |
| length | NumberComparator | Comparator for the collection length. |
| parent | NullableTeamFilter | Filters that the teams parent must satisfy. |

## TeamCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| name | String | The name of the team. |
| description | String | The description of the team. |
| key | String | The key of the team. If not given, the key will be generated based on the name of the team. |
| icon | String | The icon of the team. |
| color | String | The color of the team. |
| cyclesEnabled | Boolean | Whether the team uses cycles. |
| cycleStartDay | Float | The day of the week that a new cycle starts. |
| cycleDuration | Int | The duration of each cycle in weeks. |
| cycleCooldownTime | Int | The cooldown time after each cycle in weeks. |
| cycleIssueAutoAssignStarted | Boolean | Auto assign started issues to current active cycle setting. |
| cycleIssueAutoAssignCompleted | Boolean | Auto assign completed issues to current active cycle setting. |
| cycleLockToActive | Boolean | Only allow issues issues with cycles in Active Issues. |
| upcomingCycleCount | Float | How many upcoming cycles to create. |
| triageEnabled | Boolean | Whether triage mode is enabled for the team. |
| requirePriorityToLeaveTriage | Boolean | Whether an issue needs to have a priority set before leaving triage. |
| timezone | String | The timezone of the team. |
| inheritIssueEstimation | Boolean | Whether the team should inherit estimation settings from its parent. Only applies to sub-teams. |
| inheritWorkflowStatuses | Boolean | [Internal] Whether the team should inherit workflow statuses from its parent. |
| issueEstimationType | String | The issue estimation type to use. Must be one of "notUsed", "exponential", "fibonacci", "linear", "tShirt". |
| issueEstimationAllowZero | Boolean | Whether to allow zeros in issues estimates. |
| setIssueSortOrderOnStateChange | String | Whether to move issues to bottom of the column when changing state. |
| issueEstimationExtended | Boolean | Whether to add additional points to the estimate scale. |
| defaultIssueEstimate | Float | What to use as an default estimate for unestimated issues. |
| groupIssueHistory | Boolean | Whether to group recent issue history entries. |
| defaultTemplateForMembersId | String | The identifier of the default template for members of this team. |
| defaultTemplateForNonMembersId | String | The identifier of the default template for non-members of this team. |
| defaultProjectTemplateId | String | The identifier of the default project template of this team. |
| private | Boolean | Internal. Whether the team is private or not. |
| autoClosePeriod | Float | Period after which issues are automatically closed, in months. |
| autoCloseStateId | String | The canceled workflow state which auto closed issues will be set to. |
| autoArchivePeriod | Float | Period after which closed and completed issues are automatically archived, in months. 0 means disabled. |
| markedAsDuplicateWorkflowStateId | String | The workflow state into which issues are moved when they are marked as a duplicate of another issue. |
| parentId | String | The parent team ID. |
| inheritProductIntelligenceScope | Boolean | [Internal] Whether the team should inherit its product intelligence scope from its parent. Only applies to sub-teams. |
| productIntelligenceScope | ProductIntelligenceScope | [Internal] The scope of product intelligence suggestion data for the team. |

## TeamFilter
Team filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| name | StringComparator | Comparator for the team name. |
| key | StringComparator | Comparator for the team key. |
| description | NullableStringComparator | Comparator for the team description. |
| private | BooleanComparator | Comparator for the team privacy. |
| issues | IssueCollectionFilter | Filters that the teams issues must satisfy. |
| parent | NullableTeamFilter | Filters that the teams parent must satisfy. |
| and | LIST | Compound filters, all of which need to be matched by the team. |
| or | LIST | Compound filters, one of which need to be matched by the team. |

## TeamMembershipCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| userId | String | The identifier of the user associated with the membership. |
| teamId | String | The identifier of the team associated with the membership. |
| owner | Boolean | Internal. Whether the user is the owner of the team. |
| sortOrder | Float | The position of the item in the users list. |

## TeamMembershipUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| owner | Boolean | Internal. Whether the user is the owner of the team. |
| sortOrder | Float | The position of the item in the users list. |

## TeamSecuritySettingsInput
| Field | Type | Description |
|-------|------|-------------|
| labelManagement | TeamRoleType | The minimum team role required to manage labels in the team. |
| memberManagement | TeamRoleType | The minimum team role required to manage full workspace members (non-guests) in the team. |
| teamManagement | TeamRoleType | The minimum team role required to manage team settings. |
| templateManagement | TeamRoleType | The minimum team role required to manage templates in the team. |

## TeamSort
Issue team sorting options.

| Field | Type | Description |
|-------|------|-------------|
| nulls | PaginationNulls | Whether nulls should be sorted first or last |
| order | PaginationSortOrder | The order for the individual sort |

## TeamUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| name | String | The name of the team. |
| description | String | The description of the team. |
| key | String | The key of the team. |
| icon | String | The icon of the team. |
| color | String | The color of the team. |
| cyclesEnabled | Boolean | Whether the team uses cycles. |
| cycleStartDay | Float | The day of the week that a new cycle starts. |
| cycleDuration | Int | The duration of each cycle in weeks. |
| cycleCooldownTime | Int | The cooldown time after each cycle in weeks. |
| cycleIssueAutoAssignStarted | Boolean | Auto assign started issues to current active cycle setting. |
| cycleIssueAutoAssignCompleted | Boolean | Auto assign completed issues to current active cycle setting. |
| cycleLockToActive | Boolean | Only allow issues with cycles in Active Issues. |
| cycleEnabledStartDate | DateTime | The date to begin cycles on. |
| upcomingCycleCount | Float | How many upcoming cycles to create. |
| timezone | String | The timezone of the team. |
| inheritIssueEstimation | Boolean | Whether the team should inherit estimation settings from its parent. Only applies to sub-teams. |
| issueEstimationType | String | The issue estimation type to use. Must be one of "notUsed", "exponential", "fibonacci", "linear", "tShirt". |
| issueEstimationAllowZero | Boolean | Whether to allow zeros in issues estimates. |
| setIssueSortOrderOnStateChange | String | Whether to move issues to bottom of the column when changing state. |
| issueEstimationExtended | Boolean | Whether to add additional points to the estimate scale. |
| defaultIssueEstimate | Float | What to use as an default estimate for unestimated issues. |
| slackNewIssue | Boolean | Whether to send new issue notifications to Slack. |
| slackIssueComments | Boolean | Whether to send new issue comment notifications to Slack. |
| slackIssueStatuses | Boolean | Whether to send issue status update notifications to Slack. |
| groupIssueHistory | Boolean | Whether to group recent issue history entries. |
| aiThreadSummariesEnabled | Boolean | Whether to enable resolved thread AI summaries. |
| aiDiscussionSummariesEnabled | Boolean | Whether to enable AI discussion summaries for issues. |
| defaultTemplateForMembersId | String | The identifier of the default template for members of this team. |
| defaultTemplateForNonMembersId | String | The identifier of the default template for non-members of this team. |
| defaultProjectTemplateId | String | The identifier of the default project template of this team. |
| private | Boolean | Whether the team is private or not. |
| triageEnabled | Boolean | Whether triage mode is enabled for the team. |
| requirePriorityToLeaveTriage | Boolean | Whether an issue needs to have a priority set before leaving triage. |
| defaultIssueStateId | String | Default status for newly created issues. |
| autoClosePeriod | Float | Period after which issues are automatically closed, in months. |
| autoCloseStateId | String | The canceled workflow state which auto closed issues will be set to. |
| autoCloseParentIssues | Boolean | Whether to automatically close a parent issue in this team if all its sub-issues are closed. |
| autoCloseChildIssues | Boolean | Whether to automatically close all sub-issues when a parent issue in this team is closed. |
| autoArchivePeriod | Float | Period after which closed and completed issues are automatically archived, in months. |
| markedAsDuplicateWorkflowStateId | String | The workflow state into which issues are moved when they are marked as a duplicate of another issue. |
| joinByDefault | Boolean | Whether new users should join this team by default. Mutation restricted to workspace admins or owners! |
| scimManaged | Boolean | Whether the team is managed by SCIM integration. Mutation restricted to workspace admins or owners and only unsetting is allowed! |
| parentId | String | The parent team ID. |
| inheritWorkflowStatuses | Boolean | [Internal] Whether the team should inherit workflow statuses from its parent. |
| inheritProductIntelligenceScope | Boolean | [Internal] Whether the team should inherit its product intelligence scope from its parent. Only applies to sub-teams. |
| productIntelligenceScope | ProductIntelligenceScope | [Internal] The scope of product intelligence suggestion data for the team. |
| securitySettings | TeamSecuritySettingsInput | The security settings for the team. |
| allMembersCanJoin | Boolean | Whether all members in the workspace can join the team. Only used for public teams. |
| retiredAt | DateTime | When the team was retired. |
| handleSubTeamsOnRetirement | TeamRetirementSubTeamHandling | [Internal] How to handle sub-teams when retiring. Required if the team has active sub-teams. |

## WorkflowStateCreateInput
| Field | Type | Description |
|-------|------|-------------|
| id | String | The identifier in UUID v4 format. If none is provided, the backend will generate one. |
| type | String | The workflow type. |
| name | String | The name of the state. |
| color | String | The color of the state. |
| description | String | The description of the state. |
| position | Float | The position of the state. |
| teamId | String | The team associated with the state. |

## WorkflowStateFilter
Workflow state filtering options.

| Field | Type | Description |
|-------|------|-------------|
| id | IDComparator | Comparator for the identifier. |
| createdAt | DateComparator | Comparator for the created at date. |
| updatedAt | DateComparator | Comparator for the updated at date. |
| name | StringComparator | Comparator for the workflow state name. |
| description | StringComparator | Comparator for the workflow state description. |
| position | NumberComparator | Comparator for the workflow state position. |
| type | StringComparator | Comparator for the workflow state type. Possible values are "triage", "backlog", "unstarted", "started", "completed", "canceled". |
| team | TeamFilter | Filters that the workflow states team must satisfy. |
| issues | IssueCollectionFilter | Filters that the workflow states issues must satisfy. |
| and | LIST | Compound filters, all of which need to be matched by the workflow state. |
| or | LIST | Compound filters, one of which need to be matched by the workflow state. |

## WorkflowStateSort
Issue workflow state sorting options.

| Field | Type | Description |
|-------|------|-------------|
| nulls | PaginationNulls | Whether nulls should be sorted first or last |
| order | PaginationSortOrder | The order for the individual sort |
| closedIssuesOrderedByRecency | Boolean | Whether to sort closed issues by recency |

## WorkflowStateUpdateInput
| Field | Type | Description |
|-------|------|-------------|
| name | String | The name of the state. |
| color | String | The color of the state. |
| description | String | The description of the state. |
| position | Float | The position of the state. |
