
# Washing Machine Status System

## Project Overview  
This project is a real-time **Washing Machine Status System** that monitors and displays the availability of washing machines. The system uses **WebSockets** to receive live status updates from an **ESP8266-based microcontroller**, which sends data to the backend. The frontend dynamically updates the UI based on the received data.

## Tech Stack  

### **Frontend (React.js)**  
- **React.js** – For building the user interface  
- **Tailwind CSS** – For styling and responsiveness  
- **Socket.io-client** – For real-time WebSocket communication  

### **Backend (Node.js & Express.js)**  
- **Express.js** – For handling API requests  
- **Socket.io** – For real-time communication  
- **Cors & Body-parser** – Middleware for API request handling  

### **Hardware**  
- **ESP8266** – Sends machine status updates to the server via HTTP POST requests.  

---

## Installation & Setup  

Follow these steps to run the project locally.  

### **1. Clone the Repository**  
```sh
git clone https://github.com/Alok2580/Washing-Machine-Status-System.git
cd Washing-Machine-Status-System
```

### **2. Backend Setup**  
```sh
cd backend
npm install   # Install dependencies
nodemon server.js  # Start the backend server
```

### **3. Frontend Setup**  
```sh
cd frontend
npm install   # Install dependencies
npm run dev  # Start the React app
```

---

## Real-Time Communication Workflow  
1. The **ESP8266** sends HTTP POST requests with machine status to the backend.  
2. The **Node.js server** receives this data and broadcasts it via **WebSockets** to connected frontend clients.  
3. The **React frontend** listens for WebSocket events and updates the UI instantly.  

---

## License  
This project is open-source and available under the **MIT License**.  