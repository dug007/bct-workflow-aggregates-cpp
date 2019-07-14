#pragma once

#include <string>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         /// <summary>
         /// 
         /// </summary>
         class ComputeRule
         {
         public:
            ComputeRule(std::string id, std::string field, std::string condition, std::string expression, std::string versions);
            std::string FieldName();
            std::string Id();
            std::string Condition();
            std::string Expression();
            bool InVersion(int16_t ver);
         private:
            std::string _field;
            std::string _id;
            std::string _condition;
            std::string _expression;
            std::string _versions;
         };
      }
   }
}

