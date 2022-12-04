import express from 'express';
import show from './routes/show_answer.js';
import Middleware from './middlewares/configurations.js';
import conexao from './config/database.js';
import * as dotenv from 'dotenv'
import mongoose from 'mongoose'

dotenv.config();

const app = express();

// Conecta com o "db" do mongo
conexao()

Middleware.bodyParser(app);
Middleware.cors(app);
Middleware.principalFile(app);


app.use("/posta", show)

app.listen(3001, () => {
    console.log(`Server is running in http://localhost:${3001}`)
})

