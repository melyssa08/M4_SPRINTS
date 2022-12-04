import  express  from "express";
import Show from "../controllers/show_answer.js";

var show = express.Router()

show.post('/resultado', Show.post)
show.get('/resultadoESP', Show.get)

export default show