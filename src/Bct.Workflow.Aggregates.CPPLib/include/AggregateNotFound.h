#pragma once

#include <exception>
#include <string>

namespace Bct
{
   namespace Workflow
   {
      namespace Aggregates
      {
         class AggregateNotFound : public std::exception
         {
         public:
            /// <summary>
            /// Instantiate an AggregateNotFound exception which is thrown if no aggregate exists or it is empty
            /// </summary>
            /// <param name="aggregateName">Associated aggregate name for exception</param>
            AggregateNotFound(const std::string& aggregateName);

            /// <summary>
            /// Destructor
            /// </summary>
            virtual ~AggregateNotFound() throw();

            /// <summary>
            /// Error message for the exception
            /// </summary>
            /// <returns>The error message for this exception</returns>
            virtual const char * what() const throw();

            /// <summary>
            /// Aggregate name for exception
            /// </summary>
            /// <returns>Aggregate name associated with this exception</returns>
            const std::string& aggregateName() const;

         private:
            std::string _errorMessage;
            std::string _aggregateName;

         };

      }
   }
}
