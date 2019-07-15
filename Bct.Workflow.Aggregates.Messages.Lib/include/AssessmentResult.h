#pragma once

#include <string>
#include <vector>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class AssessmentResult
         {
         public:
            AssessmentResult();
            void addError(std::string id, std::string context);
            std::vector<std::string> getErrorIds();
            std::vector<std::string> getContexts();
            bool isSuccess();
            bool isFailure();
         private:
            std::vector<std::string> _ids;
            std::vector<std::string> _contexts;
         };
      }
   }
}
