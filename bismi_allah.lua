--بسم الله الرحمن الرحيم

print("[lua] بسم الله الرحمن الرحيم")

g = require("include.elg")
elgtk = require("include.elgtk")

activate = function(app, user_data)
    window = elgtk.application_window.new(app)
    elgtk.window.set_title(window, "BismiAllah")

    elgtk.widget.show(window)
end

app = elgtk.application.new("BismiAllah.BismiAllah.BismiAllah", G_APPLICATION_FLAGS_NONE)
g.signal.connect(app, "activate", activate, 0)
status = g.application.run(app, 0, 0)

