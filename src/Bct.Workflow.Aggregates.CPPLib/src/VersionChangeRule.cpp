#include "VersionChangeRule.h"

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {

         VersionChangeRule::VersionChangeRule(int32_t fieldId, int16_t toVersion, std::string condition, std::string expression)
            : _fieldId(fieldId),  _toVersion(toVersion), _expression(expression), _condition(condition)
         {
         };

         int32_t VersionChangeRule::fieldId()
         {
            return _fieldId;
         }
         int16_t VersionChangeRule::ToVersion()
         {
            return _toVersion;
         }
         std::string VersionChangeRule::Expression()
         {
            return _expression;
         }
         std::string VersionChangeRule::Condition()
         {
            return _condition;
         }
      }
   }
}