#pragma once

#include <string>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class VersionChangeRule
         {
         public:
            VersionChangeRule(std::string field, std::string fromMinor, std::string toMinor, std::string expression)
               : _field(field), _fromMinor(fromMinor), _toMinor(toMinor), _expression(expression) {};
            std::string Field() { return _field; }
            std::string FromMinor() { return _fromMinor; }
            std::string ToMinor() { return _toMinor; }
            std::string Expression() { return _expression; }

         private:
            std::string _field;
            std::string _fromMinor;
            std::string _toMinor;
            std::string _expression;
         };
      }
   }
}
