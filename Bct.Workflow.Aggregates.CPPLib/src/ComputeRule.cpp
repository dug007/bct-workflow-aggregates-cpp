#include "ComputeRule.h"
#include <sstream>


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         ComputeRule::ComputeRule(std::string const &id, int16_t fieldId, std::string const &condition, std::string const &expression, std::string const &versions) :
            _id(id), _fieldId(fieldId), _condition(condition), _expression(expression), _versions(versions)
         {
         };
         int16_t ComputeRule::FieldId()
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
         bool ComputeRule::InVersion(int16_t ver)
         {
            std::ostringstream ss;
            ss << '.' << ver << '.';
            std::string verStr = ss.str();
            std::size_t f = _versions.find(verStr);
            return (f != std::string::npos);
         }
      };
   }
}


