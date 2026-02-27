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