import mongoose from "mongoose"


const terminoRodada = new mongoose.Schema({
    playerWin: String
  });

const modelo = mongoose.model('modeloCriado', terminoRodada);


export default modelo