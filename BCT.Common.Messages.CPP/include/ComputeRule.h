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
         private:
            std::string _field;
            std::string _condition;
            std::string _expression;
         };
      }
   }
}

