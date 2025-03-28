const express = require('express');
const bodyParser = require('body-parser');
const http = require('http');
const socketIo = require('socket.io');
const cors = require('cors');

const app = express();


app.use(bodyParser.json());
app.use(cors());

const server = http.createServer(app);
const io = socketIo(server, {
  cors: { origin: '*' }
});


app.post('/api/status', (req, res) => {
  const statusData = req.body;
  console.log("Received data:", statusData);
  
  
  io.emit('statusUpdate', statusData);
  

  res.status(200).json({ message: 'Status received' });
});


app.get('/', (req, res) => {
  res.send('Washing Machine Status Server is running');
});


const PORT = 3000;
server.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
