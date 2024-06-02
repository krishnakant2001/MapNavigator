require('dotenv').config()
const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const { execFile } = require('child_process');

const app = express();
const PORT = process.env.PORT || 5000;

app.use(bodyParser.json());
app.use(cors());

app.post('/map', (req, res) => {
    const { src, des } = req.body;

    execFile('./map', [src, des], (error, stdout, stderr) => {
        if (error) {
            res.status(500).json({ error: stderr });
            return;
        }
        res.json({ route: JSON.parse(stdout) });
    });
});

app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});
