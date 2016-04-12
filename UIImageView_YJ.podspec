#
# Be sure to run `pod lib lint UIImageView_YJ.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = "UIImageView_YJ"
  s.version          = "0.1.2"
  s.summary          = "UIImageView_YJ is a UIImageView class extension that can use new contentMode to display it's contents."
  s.description      = <<-DESC
UIImageView_YJ is a UIImageView class extension that can use new contentMode to display it's contents. Simply using yj_contentMode instead of contentMode.
                       DESC
  s.homepage         = "https://github.com/huang-kun/UIImageView_YJ"
  # s.screenshots     = "www.example.com/screenshots_1", "www.example.com/screenshots_2"
  s.license          = 'MIT'
  s.author           = { "huang-kun" => "jack-huang-developer@foxmail.com" }
  s.source           = { :git => "https://github.com/huang-kun/UIImageView_YJ.git", :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.platform     = :ios, '6.0'
  s.requires_arc = true

  s.source_files = 'UIImageView_YJ/**/*'
  s.public_header_files = 'UIImageView_YJ/**/*.h'
  s.frameworks = 'UIKit'
  # s.dependency 'AFNetworking', '~> 2.3'
end
