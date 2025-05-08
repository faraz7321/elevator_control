#!/bin/bash

# Variables
REPO_URL="https://github.com/faraz7321/elevator_control.git"
PROJECT_DIR="/home/pi/elevator_control"
DOCKER_IMAGE="elevator-control"

# Update & Install Dependencies
echo "Updating system and installing dependencies..."
sudo apt-get update && sudo apt-get upgrade -y
sudo apt-get install -y \
    build-essential \
    cmake \
    git \
    libssl-dev \
    zlib1g-dev \
    libcurl4-openssl-dev \
    libboost-all-dev \
    libjsoncpp-dev \
    libsqlite3-dev \
    libwebsocketpp-dev \
    wget \
    curl \
    unzip \
    lsb-release \
    && rm -rf /var/lib/apt/lists/*

# Install Docker if not already installed
echo "Installing Docker..."
if ! command -v docker &>/dev/null; then
    curl -sSL https://get.docker.com | sh
    sudo usermod -aG docker $USER
    echo "Docker installed. Please log out and back in to apply Docker permissions."
else
    echo "Docker is already installed."
fi

# Clone the repository (or skip if already cloned)
if [ ! -d "$PROJECT_DIR" ]; then
    echo "Cloning repository..."
    git clone $REPO_URL $PROJECT_DIR
else
    echo "Repository already cloned in $PROJECT_DIR"
fi

cd $PROJECT_DIR

# Build Docker image
echo "Building Docker image..."
docker build -t $DOCKER_IMAGE .

# Run the Docker container
echo "Running Docker container..."
docker run -it --rm $DOCKER_IMAGE

# Optionally: Set up a systemd service to auto-start the container
echo "Setting up systemd service to auto-run on boot..."
SERVICE_FILE="/etc/systemd/system/elevator_control.service"

cat <<EOF | sudo tee $SERVICE_FILE
[Unit]
Description=Elevator Control System
After=network.target

[Service]
ExecStart=/usr/bin/docker run --rm $DOCKER_IMAGE
WorkingDirectory=$PROJECT_DIR
User=pi
Group=pi
Restart=always
Environment=ROBOT_HOST=192.168.1.100
Environment=ROBOT_SECRET=secret123
Environment=ROBOT_BUSINESS_ID=bizz_456
Environment=ELEVATOR_TYPE=geprog
Environment=ELEVATOR_HOST=192.168.1.150

[Install]
WantedBy=multi-user.target
EOF

# Step 8: Reload systemd, enable, and start the service
echo "Enabling and starting the systemd service..."
sudo systemctl daemon-reload
sudo systemctl enable elevator_control.service
sudo systemctl start elevator_control.service

echo "Setup complete! The system will start on boot, and you can control it via systemd."
