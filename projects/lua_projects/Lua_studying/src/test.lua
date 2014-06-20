
--print("hello lua")

local label = cc.LabelTTF:create("Hello lua", "Courier", 50)
label:setPosition(cc.p(300, 300))

local scene = cc.Scene:create()

local layer = cc.Layer:create()

scene:addChild(layer)
layer:addChild(label)
cc.Director:getInstance():runWithScene(scene)
