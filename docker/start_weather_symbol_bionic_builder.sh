#! /bin/bash

image_name="weather_symbol_builder"
container_name="weather-symbol-builder"
volume_src="/home/borgem/projects/git/weather_symbol"
volume_build="/media/borgem/backup_pc4816/volumes/weather_symbol_builder"


name=$(docker ps -a --filter "name=$container_name" --format "{{.Names}}")

if [ $? -ne 0 ]; then
  echo "Failed to get the status information for container '$container_name'."
  exit 1
fi

if [ -n "$name" ]; then 
  name=$(docker ps --filter "name=$container_name" --format "{{.Names}}")

  if [ $? -ne 0 ]; then
    echo "Failed to get the status information for container '$container_name' (*)."
    exit 1
  fi

  if [ -n "$name" ]; then 
    echo "Container '$container_name' is running."
    exit 0
  else
    echo "Restarting container '$container_name'."
    if ! docker restart $container_name ; then 
      echo "Failed to restart '$container_name'."
      exit 1
    else 
      echo "Restarted '$container_name'."
      exit 0
    fi
  fi
fi

echo "Creating container '$container_name' using image '$image_name'."


docker run -d \
  -v $volume_build:/build \
  -v $volume_src:/src \
  --name $container_name \
  $image_name  
