#! /bin/bash
container_name="weather-symbol-builder"

name=$(docker ps --filter "name=$container_name" --format "{{.Names}}")

if [ $? -ne 0 ]; then
  echo "Failed to get the status information for container '$container_name'."
  exit 1
fi

if [ -z "$name" ]; then 
  echo "Container '$name' is not running."
  echo "Try to start it with 'start_weather_symbol_bionic_builder.sh'"
  exit 1
fi

docker exec -ti $name bash
