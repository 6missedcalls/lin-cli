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
