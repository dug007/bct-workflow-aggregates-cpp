#pragma once

#include <string>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// This is version change rule TBD
         /// </summary>
         class VersionChangeRule
         {
         public:
            /// <summary>
            /// Testing
            /// </summary>
            /// <param name="field">the name</param>
            /// <param name="fromMinor">from minor</param>
            /// <param name="toMinor"></param>
            /// <param name="expression"></param>
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
