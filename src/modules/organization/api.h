#pragma once

#include "modules/organization/model.h"

namespace organization_api {

// Get the current organization info
Organization get_organization();

// Get the current API rate limit status
RateLimitStatus get_rate_limit();

}  // namespace organization_api
