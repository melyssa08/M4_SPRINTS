import bodyParser from "body-parser";
import cors from "cors";
import express from "express";

class Middleware {
    static bodyParser (app) {
        app.use(bodyParser.json())
    }

    static cors (app) {
        app.use(
            cors({
				origin: '*'
			})
        )
    } 
    static principalFile(app) {
        app.use(express.static('../frontend/src/view/'));
    }
}

export default Middleware 