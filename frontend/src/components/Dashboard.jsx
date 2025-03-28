
import React, { useState, useEffect } from "react";
import io from "socket.io-client";

const Dashboard = () => {

  const [machines, setMachines] = useState([
    { id: 1, name: "Machine 1", status: false, img: "/machine1.jpg" },
    { id: 2, name: "Machine 2", status: false, img: "/machine2.jpg" },
    { id: 3, name: "Machine 3", status: false, img: "/machine3.jpg" },
    { id: 4, name: "Machine 4", status: false, img: "/machine4.jpg" },
  ]);

  useEffect(() => {
    const socket = io("http://192.168.43.56:3000"); 

    socket.on("statusUpdate", (data) => {
      console.log("Received data from socket:", data);
      setMachines((prevMachines) =>
        prevMachines.map((machine) => ({
          ...machine,
          status: data[`machine${machine.id}`],
        }))
      );
    });

    return () => {
      socket.disconnect();
    };
  }, []);

  return (
    <section id="home" className="flex-1 py-8">
      <div className="container mx-auto px-4">
        <h1 className="text-3xl font-bold text-center mb-6 pt-5 py-20 ">
          Washing Machine Dashboard
        </h1>
        <div className="grid grid-cols-1 md:grid-cols-2 gap-6 justify-items-center">
          {machines.map((machine) => (
            <div key={machine.id} className="card w-80 bg-base-100 shadow-xl">
              <figure>
                <img
                  src={machine.img}
                  alt={machine.name}
                  className="h-48 w-full object-cover"
                />
              </figure>
              <div className="card-body items-center text-center">
                <h2 className="card-title">{machine.name}</h2>
                <button
                  className={`btn ${
                    machine.status ? "btn-error" : "btn-success"
                  }`}
                >
                  {machine.status ? "Occupied" : "Available"}
                </button>
              </div>
            </div>
          ))}
        </div>
        <div className="container mx-auto px-4 my-10 pt-20 mb-0 flex flex-col items-center gap-8">
         
          <div className="w-full text-center">
            <h2 className="text-5xl font-bold mt-8 mb-6 bg-gradient-to-r from-red-400 via-orange-400 via-yellow-400 via-green-400 via-blue-400 via-indigo-400 to-violet-400 bg-clip-text text-transparent">
              Contact Us
            </h2>
            <div className="flex flex-col md:flex-row justify-center items-center gap-40">
     
              <div className="flex flex-col items-center p-6">
                <span className="font-semibold text-lg">Chetan</span>
                <span className="text-sm">chetansharma777555@gmail.com</span>
                <span className="text-sm">7668751288</span>
              </div>
       
              <div className="flex flex-col items-center p-6">
                <span className="font-semibold text-lg">Alok</span>
                <span className="text-sm">aloksingh15122004@gmail.com</span>
                <span className="text-sm">7905780360</span>
              </div>
           
              <div className="flex flex-col items-center p-6">
                <span className="font-semibold text-lg">Shyam</span>
                <span className="text-sm">shyam7512@gmail.com</span>
                <span className="text-sm">7004995201</span>
              </div>
            </div>
          </div>
        </div>
      </div>
    </section>
  );
};

export default Dashboard;
