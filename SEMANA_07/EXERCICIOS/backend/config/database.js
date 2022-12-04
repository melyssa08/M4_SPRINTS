import mongoose from 'mongoose'
import * as dotenv from 'dotenv' 
dotenv.config()


// conexão com a database criada

var conexao = () => { 
  mongoose.connect(process.env.MONGO_URI, 
{useNewUrlParser: true, useUnifiedTopology: true})
.then((resposta) => {
  console.log('Conexão com o database criada')
}).catch((resposta) => {
  console.error('Deu erro na conexão')
})
}

export default conexao