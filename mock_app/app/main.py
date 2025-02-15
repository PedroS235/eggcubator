from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles


app = FastAPI(
    title="Eggcubator Mock App",
)


@app.get("/temperature")
def get_temperature():
    return {"current_temperature": 25.4, "target_temperature": 30}


@app.post("/temperature")
def set_temperature(target: float):
    print(f"Setting target temperature to {target}")
    return {"status": "OK"}


@app.get("/humidity")
def get_humidity():
    return {"current_humidity": 25.4, "target_humidity": 20}


@app.post("/humidity")
def set_humidity(target: float):
    print(f"Setting target humidity to {target}")
    return {"status": "OK"}


@app.post("/incubation/start")
def start_incubation(egg_type: int):
    print(f"Starting incubation for the egg type {egg_type}")
    return {"status": "OK"}


@app.post("/incubation/stop")
def stop_incubation():
    print(f"Stopping current ongoing incubation")
    return {"status": "OK"}


@app.get("/incubation")
def get_incubation():
    print(f"Stopping current ongoing incubation")
    return {
        "state": "IN_INCUBATION",
        "egg_type": 0,
        "time_left": 1234,
        "current_day": 2,
    }


# Serve website
app.mount("/", StaticFiles(directory="static", html=True), name="static")
