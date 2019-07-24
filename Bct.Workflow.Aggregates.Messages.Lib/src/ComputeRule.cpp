#include "ComputeRule.h"
#include <sstream>


namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         ComputeRule::ComputeRule(std::string id, std::string field, std::string condition, std::string expression, std::string versions) :
            _id(id), _field(field), _condition(condition), _expression(expression), _versions(versions)
         {
         };
         std::string ComputeRule::FieldName()
         {
            return _field;
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


