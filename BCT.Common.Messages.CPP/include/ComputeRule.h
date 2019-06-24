#pragma once

#include <string>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class ComputeRule
         {
         public:
            ComputeRule(std::string field, std::string condition, std::string expression) : _field(field), _condition(condition), _expression(expression) {};
            std::string FieldName()
            {
               return _field;
            }
            std::string Condition()
            {
               return _condition;
            }
            std::string Expression()
            {
               return _expression;
            }
         private:
            std::string _field;
            std::string _condition;
            std::string _expression;
         };
      }
   }
}

