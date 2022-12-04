import modelo from "../models/terminoRodada.js" 

class Show {
    static post (req, res) {

        modelo.create(req.body)
        res.json('Resposta enviada')

    }

    static get (req, res) {

        modelo.find().then(function (data) {
            res.json([data.length ,data[data.length - 1]])
        })
    }

}


export default Show