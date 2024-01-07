--بسم الله الرحمن الرحيم

print("[lua] بسم الله الرحمن الرحيم")

g = require("include.elg")
elgtk = require("include.elgtk")

elgtk.window.set_title(window, "bismi_allah")
g.signal.connect(button, "clicked", function() print("[lua] button clicked") end, 0)

