#!/bin/bash

# Store off the container name and move past it to the build arguments
containerName=$1
readonly BUILDER=$1
shift

# Attempt to get the common directory from the environment.
#  If not set assume the default location
commonDirectory=${COMDIR:-$(pwd)/Common}
dockerDirectory=${DOCKERDIR:-$(pwd)/Docker}

function buildImageAvailable
{
   if [[ "$(docker image inspect $BUILDER >/dev/null 2>&1 && echo true || echo false)" == "true" ]]; then
      return 0
   else
      return 1
   fi
}

function builderRunning
{
   if [[ "$(docker inspect -f '{{.State.Running}}' $1 2>/dev/null)" == "true" ]]; then
      return 0
   else
      return 1
   fi
}

if ! builderRunning $containerName; then
   if buildImageAvailable; then
      echo "Builder not running, attempting to start."
      docker run -i -d --rm \
             -e LOCAL_USER_ID=$(id -u) \
             --workdir="/app" \
             --name $containerName \
             -v $(pwd):/app:Z \
             $BUILDER


      if ! builderRunning $containerName; then
         echo "Problem starting docker container: $containerName."
         exit 1
      fi
   else
      if [[ "$(command -v docker && echo true || echo false)" == "true" ]]; then
         echo "Install docker first."
         exit 1
      else
         echo "Builder image $BUILDER is not available, need to create it first!"
         exit 1
      fi
   fi
else
   echo "Container already started: $containerName"
fi

# Make the args a single string
args="${@}"
docker exec --user $(id -u) -it $containerName sh -c "$args"
result=$?
docker stop $containerName
exit ${result}
