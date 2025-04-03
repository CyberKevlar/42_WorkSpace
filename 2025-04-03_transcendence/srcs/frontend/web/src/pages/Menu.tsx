import React from "react";
import { useNavigate } from "react-router-dom";

const GameMenu: React.FC = () => {
  const navigate = useNavigate();

  const handlePlayerSelection = (players: number) => {
    // Redirige al juego con el número de jugadores seleccionado
    navigate(`/game?players=${players}`);
  };

  return (
    <div className="min-h-screen flex items-center justify-center bg-gradient-to-br from-slate-900 to-blue-900 text-white">
      <div className="text-center">
        <h1 className="text-4xl font-bold mb-8">¿Como quieres jugar?</h1>
        <div className="space-y-6">
            <button
                onClick={() => handlePlayerSelection(1)}
                className="bg-blue-600 text-white px-8 py-3 rounded-lg hover:bg-blue-700 transition duration-300">1 VS IA
            </button>
            <button
                onClick={() => handlePlayerSelection(2)}
                className="bg-blue-600 text-white px-8 py-3 rounded-lg hover:bg-blue-700 transition duration-300">PVP
            </button>
            <button
                onClick={() => handlePlayerSelection(3)}
                className="bg-blue-600 text-white px-8 py-3 rounded-lg hover:bg-blue-700 transition duration-300">¡BATLE ROYALE!
            </button>
        </div>
      </div>
    </div>
  );
};

export default GameMenu;