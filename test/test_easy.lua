local HAS_RUNNER = not not lunit
local lunit      = require "lunit"
local TEST_CASE  = assert(lunit.TEST_CASE)
local skip       = lunit.skip or function() end

local curl       = require "lcurl"
local scurl      = require "lcurl.safe"
local url        = "http://example.com"
local fname      = "./test.download"

local _ENV = TEST_CASE'write_callback' do

local c, f

function teardown()
  if f then f:close() end
  os.remove(fname)
  if c then c:close() end
  f, c = nil
end

function test_write_to_file()
  f = assert(io.open(fname, "w+b"))
  c = assert(curl.easy{
    url = url;
    writefunction = f;
  })

  assert_equal(c, c:perform())
end

function test_write_to_file_abort()
  f = assert(io.open(fname, "w+b"))
  c = assert(scurl.easy{
    url = url;
    writefunction = function(str)
      return #str - 1
    end;
  })

  local _, e = assert_nil(c:perform())
  assert_equal(e, curl.error(curl.ERROR_EASY, curl.E_WRITE_ERROR))

end

end

local _ENV = TEST_CASE'escape' do

local c

function teardown()
  if c then c:close() end
  f, c = nil
end

function test()
  local e = "This%2Bis%2Ba%2Bsimple%2B%2526%2Bshort%2Btest."
  local d = "This+is+a+simple+%26+short+test."
  c = assert(curl.easy())
  assert_equal(e, c:escape(d))
  assert_equal(d, c:unescape(e))
end

end




if not HAS_RUNNER then lunit.run() end
