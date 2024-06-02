import React, { useState } from 'react';
import axios from 'axios';
import './App.css';

function App() {
    const [src, setSrc] = useState('');
    const [des, setDes] = useState('');
    const [route, setRoute] = useState([]);

    const handleSubmit = async (event) => {
        event.preventDefault();
        try {
            const response = await axios.post('http://localhost:5000/map', { src, des });
            setRoute(response.data.route);
        } catch (error) {
            console.error('Error fetching route:', error);
        }
    };

    return (
        <div className="App">
            <header className="App-header">
                <h1>Dijkstra's Algorithm Web App</h1>
                <form onSubmit={handleSubmit}>
                    <label>
                        Source:
                        <select value={src} onChange={(e) => setSrc(e.target.value)} required >
                            <option value="">Not select</option>
                            <option value="Ahemdabad">Ahemdabad</option>
                            <option value="Jaipur">Jaipur</option>
                            <option value="Agra">Agra</option>
                            <option value="Gwalior">Gwalior</option>
                            <option value="NewDelhi">NewDelhi</option>
                            <option value="Kolkata">Kolkata</option>
                            <option value="Lucknow">Lucknow</option>
                            <option value="Bhopal">Bhopal</option>
                            <option value="Chandigarh">Chandigarh</option>
                            <option value="Morena">Morena</option>
                            </select>
                    </label>
                    <br />
                    <label>
                        Destination:
                        <select type="text" value={des} onChange={(e) => setDes(e.target.value)} required >
                            <option value="">Not select</option>
                            <option value="Ahemdabad">Ahemdabad</option>
                            <option value="Jaipur">Jaipur</option>
                            <option value="Agra">Agra</option>
                            <option value="Gwalior">Gwalior</option>
                            <option value="NewDelhi">NewDelhi</option>
                            <option value="Kolkata">Kolkata</option>
                            <option value="Lucknow">Lucknow</option>
                            <option value="Bhopal">Bhopal</option>
                            <option value="Chandigarh">Chandigarh</option>
                            <option value="Morena">Morena</option>
                            </select>
                    </label>
                    <br />
                    <button type="submit">Calculate Shortest Path</button>
                </form>
                {route.length > 0 && (
                    <div>
                        <h2>Train Route:</h2>
                        <p>{route.join(' -> ')}</p>
                    </div>
                )}
            </header>
        </div>
    );
}

export default App;
