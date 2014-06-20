
--print("hello lua")

function Main()

    local self = cc.Scene:create()
    local layer

    local function init()

        layer = cc.Layer:create()
        self:addChild(layer)

        local picture = cc.Sprite:create("res/blue.png")
        picture:setPosition(cc.p(300, 300))
        layer:addChild(picture)

        layer:setTouchEnabled(true)
        
        layer:registerScriptTouchHandler(function(type, x, y)

                print(type .."  " .. x .. "," .. y)

                if picture:boundingBox():containsPoint(cc.p(x, y)) then

                    print("picture was clicked")
                end

                return true
        end)
    end
    
    init()

    return self
end



function __main()

<<<<<<< HEAD
    director = cc.Director:getInstance()

    glView = director:getOpenGLView()

    eglView:setDesignResolutionSize(800, 480, kResolutionShowAll)
=======
    --cc.EGLView:getInstance():setDesignResolutionSize(800, 480, kResolutionShowAll)
    --CCEGLView:sharedOpenGLView:setDesignResolutionSize(800, 480, kResolutionShowAll) 
    --auto director = Director::getInstance();
    --auto eglView = EGLView::getInstance();
    --director->setOpenGLView(eglView);
    --eglView->setDesignResolutionSize(1136, 640, ResolutionPolicy::SHOW_ALL);
>>>>>>> FETCH_HEAD

    director:runWithScene(Main())

end

__main()
