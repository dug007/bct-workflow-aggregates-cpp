#include "ComputeRule.h"
#include <sstream>


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         ComputeRule::ComputeRule(std::string const &id, int16_t fieldId, std::string const &condition, std::string const &expression) :
            _id(id), _fieldId(fieldId), _condition(condition), _expression(expression)
         {
         };
         int16_t ComputeRule::fieldId()
         {
            return _fieldId;
         }
         std::string ComputeRule::Id()
         {
            return _id;
         }
         std::string ComputeRule::Condition()
         {
            return _condition;
         }
         std::string ComputeRule::Expression()
         {
            return _expression;
         }
      };
   }
}


