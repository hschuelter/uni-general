class Settings:
    framerate = 0
    resolution = (0, 0)
    font = None
    clock = None

    def __init__(self):
        # self.resolution = (960, 720)  # WIDTH, HEIGHT
        self.resolution = (1280, 720)   # WIDTH, HEIGHT
        self.framerate = 60
        font = None
        clock = None

    def __init__(self, resolution, framerate):
        self.resolution = resolution
        self.framerate = framerate
        font = None
        clock = None
