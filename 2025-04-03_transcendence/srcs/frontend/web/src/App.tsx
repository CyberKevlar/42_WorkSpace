import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import Home from "./pages/Home";
import Login from "./pages/Login";
import Signup from "./pages/Signup";
import Menu from "./pages/Menu";
import Game from "./pages/Game";
import Status from "./pages/Status";
import Header from "./components/layout/Header";

function App() {
  return (
    <Router>
      <div className="flex flex-col min-h-screen bg-gray-900 text-white">
        <Header />
        <main className="flex-grow">
          <Routes>
            <Route path="/" element={<Home />} />
            <Route path="/login" element={<Login />} />
            <Route path="/signup" element={<Signup />} />
            <Route path="/menu" element={<Menu />} />
            <Route path="/game" element={<Game />} />
			      <Route path="/status" element={<Status />} />
            {/* Add more routes here as needed */}
          </Routes>
        </main>
      </div>
    </Router>
  );
}

export default App;
