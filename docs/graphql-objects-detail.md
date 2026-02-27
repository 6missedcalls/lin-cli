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
