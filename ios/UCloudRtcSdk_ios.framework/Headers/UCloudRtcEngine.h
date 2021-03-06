//
//  UCloudRtcEngine.h
//  UCloudRtcSDK
//
//  Created by tony on 2019/2/1.
//  Copyright © 2019年 ucloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger)
{
    UCloudRtcEngineModeNormal = 0,//正式
    UCloudRtcEngineModeTrival = 1,//测试
    
}UCloudRtcEngineMode;

typedef NS_ENUM(NSInteger)
{
    UCloudRtcEngineRoomType_Communicate = 0,//小班课 、视频会议  默认值
    UCloudRtcEngineRoomType_Broadcast = 1,//大班课
    
}UCloudRtcEngineRoomType;

typedef NS_ENUM(NSInteger)
{
    UCloudRtcEngine_StreamProfileUpload = 0,            // 上传权限
    UCloudRtcEngine_StreamProfileDownload = 1,          //下载权限
    UCloudRtcEngine_StreamProfileAll= 2,               //所有权限 默认值
    
} UCloudRtcEngineStreamProfile;


typedef NS_ENUM(NSInteger)
{
    
    UCloudRtcEngine_VideoProfile_180P = 0,            // 240*180  100 --- 200 15
    UCloudRtcEngine_VideoProfile_360P_1 = 1,          // 480*360  100 -- 300 15   默认值
    UCloudRtcEngine_VideoProfile_360P_2 = 2,          // 640*360  100 -- 400 20
    
    UCloudRtcEngine_VideoProfile_480P = 3,           // 640*480  100 -- 500 20
    UCloudRtcEngine_VideoProfile_720P = 4,           // 1280*720 300 -- 1000 30
//    UCloudRtcEngine_VideoProfile_1080P = 5,          // 1920*1080 500 -- 1000 30
    
} UCloudRtcEngineVideoProfile;

typedef NS_ENUM(NSInteger,UCloudRtcEngineErrorType) {
    UCloudRtcEngineErrorTypeJoinRoomError,
    UCloudRtcEngineErrorTypeRoomExist,
    UCloudRtcEngineErrorTypeTokenInvalid,
    UCloudRtcEngineErrorTypeStreamDisconnected, //流已断开
};

//发布状态
typedef NS_ENUM(NSInteger,UCloudRtcEnginePublishState) {
    UCloudRtcEnginePublishStateUnPublish = 0,
    UCloudRtcEnginePublishStatePublishing,
    UCloudRtcEnginePublishStatePublishSucceed,
    UCloudRtcEnginePublishStateRepublishing,
    UCloudRtcEnginePublishStatePublishFailed,
    UCloudRtcEnginePublishStatePublishStoped,
};

/** 本地预览视频视图的模式 */
typedef NS_ENUM(NSInteger,UCloudRtcVideoViewMode) {
    /** 等比缩放，可能有黑边 */
    UCloudRtcVideoViewModeScaleAspectFit     = 0,
    /** 等比缩放填充整View，可能有部分被裁减 */
    UCloudRtcVideoViewModeScaleAspectFill    = 1,
    /** 填充整个View */
    UCloudRtcVideoViewModeScaleToFill        = 2,
};


@class UCloudRtcEngine,UCloudRtcStream,UCloudRtcError,UCloudRtcRoomStream,UCloudRtcStreamVolume,UCloudRtcStreamStatsInfo,UCloudRtcLog,UCloudRtcRecordConfig;
@protocol UCloudRtcEngineDelegate <NSObject>
@optional

///**加入房间成功*/
//- (void)uCloudRtcEngineDidJoinRoom:(BOOL)succeed streamList:(NSMutableArray<UCloudRtcStream *> * _Nonnull)canSubStreamList;

/**退出房间*/
- (void)uCloudRtcEngineDidLeaveRoom:(UCloudRtcEngine *_Nonnull)manager;

/**与房间的连接断开*/
- (void)uCloudRtcEngineDisconnectRoom:(UCloudRtcEngine *_Nonnull)manager;


/**发布状态的变化*/
- (void)uCloudRtcEngine:(UCloudRtcEngine *_Nonnull)manager didChangePublishState:(UCloudRtcEnginePublishState)publishState;

/**收到远程流*/
- (void)uCloudRtcEngine:(UCloudRtcEngine *_Nonnull)manager receiveRemoteStream:(UCloudRtcStream *_Nonnull)stream;

/**远程流断开(本地移除对应的流)*/
- (void)uCloudRtcEngine:(UCloudRtcEngine *_Nonnull)manager didRemoveStream:(UCloudRtcStream *_Nonnull)stream;


/**新成员加入*/
- (void)uCloudRtcEngine:(UCloudRtcEngine *_Nonnull)manager memberDidJoinRoom:(NSDictionary *_Nonnull)memberInfo;

/**成员退出*/
- (void)uCloudRtcEngine:(UCloudRtcEngine *_Nonnull)manager memberDidLeaveRoom:(NSDictionary *_Nonnull)memberInfo;

/**非自动订阅模式下 可订阅流加入*/
- (void)uCloudRtcEngine:(UCloudRtcEngine *_Nonnull)channel newStreamHasJoinRoom:(UCloudRtcStream *_Nonnull)stream;

///**非自动订阅模式下 可订阅流退出*/
- (void)uCloudRtcEngine:(UCloudRtcEngine *_Nonnull)channel streamHasLeaveRoom:(UCloudRtcStream *_Nonnull)stream;

///**非自动订阅模式下 订阅成功的回调  已废弃*/
//- (void)uCloudRtcEngine:(UCloudRtcEngine *_Nonnull)channel didSubscribe:(UCloudRtcStream *_Nonnull)stream;
//
///**非自动订阅模式下 取消订阅成功的回调  已废弃*/
//- (void)uCloudRtcEngine:(UCloudRtcEngine *_Nonnull)channel didCancleSubscribe:(UCloudRtcStream *_Nonnull)stream;

/**流 状态回调*/
- (void)uCloudRtcEngine:(UCloudRtcEngine *_Nonnull)manager didReceiveStreamStatus:(NSArray<UCloudRtcStreamStatsInfo*> *_Nonnull)status;

/**流 连接失败*/
- (void)uCloudRtcEngine:(UCloudRtcEngine *_Nonnull)manager streamConnectionFailed:(NSString *_Nonnull)streamId;

/**错误的回调*/
- (void)uCloudRtcEngine:(UCloudRtcEngine *_Nonnull)manager error:(UCloudRtcError *_Nonnull)error;

/**开始视频录制的回调*/
- (void)uCloudRtcEngine:(UCloudRtcEngine *_Nonnull)manager startRecord:(NSDictionary *_Nonnull)recordResponse;

/**收到自定义消息的回调*/
- (void)uCloudRtcEngine:(UCloudRtcEngine *_Nonnull)manager receiveCustomCommand:(NSString *_Nonnull)fromUserID  content:(NSString *_Nonnull)content;

/**远端视频关闭的回调*/
- (void)uCloudRtcEngine:(UCloudRtcEngine *_Nonnull)channel remoteVideoMute:(BOOL)remoteVideoMute;

/**媒体播放器播放结束的回调*/
- (void)uCloudRtcEngine:(UCloudRtcEngine *_Nonnull)channel mediaPlayerOnPlayEnd:(BOOL)isEnd;

@end

@interface UCloudRtcEngine : NSObject

/**SDK模式  默认是: 测试  正式上线前需要切换到正式模式*/
@property (nonatomic, assign) UCloudRtcEngineMode engineMode;

/**是否自动发布  默认是: YES  必须在加入房间之前设置才会生效 否则采用默认值*/
@property (nonatomic, assign) BOOL isAutoPublish;

/**是否自动订阅  默认是: YES 必须在加入房间之前设置才会生效 否则采用默认值*/
@property (nonatomic, assign) BOOL isAutoSubscribe;

/**是否开启纯音频模式  默认否: NO  必须在加入房间之前设置才会生效 否则采用默认值*/
@property (nonatomic, assign) BOOL isOnlyAudio;

/**视频分辨率设置 默认:480*360  必须在加入房间之前设置才会生效 否则采用默认值*/
@property (nonatomic, assign) UCloudRtcEngineVideoProfile videoProfile;

/**本地流权限设置 默认:所有权限  必须在加入房间之前设置才会生效 否则采用默认值*/
@property (nonatomic, assign) UCloudRtcEngineStreamProfile streamProfile;

/**URTC 房间类型  默认是: 0  必须在加入房间之前设置才会生效 否则采用默认值*/
@property (nonatomic, assign) UCloudRtcEngineRoomType roomType;

/**是否开启免提*/
@property (nonatomic, assign, readonly) BOOL isLoudSpeaker;

@property (nonatomic, weak) id <UCloudRtcEngineDelegate> _Nullable delegate;

@property (nonatomic, readonly) UCloudRtcStream * _Nonnull localStream;

@property (nonatomic, strong) UCloudRtcLog * _Nullable logger;

/**是否开启混音*/
@property (nonatomic, assign) BOOL fileMix;

/**混音文件路径*/
@property (nonatomic, copy) NSString * _Nullable filePath;

/**混音文件是否循环播放*/
@property (nonatomic, assign) BOOL fileLoop;

/**视频编码格式 默认VP8 可选 VP8 || H264 */
@property (nonatomic, copy) NSString * _Nullable videoDefaultCodec;


//本地视频录制参数
@property (nonatomic, assign) BOOL openNativeRecord;//是否开启本地录制

@property (nonatomic, copy) NSString *outputpath;//混音文件路径


/**
 @brief 返回SDK当前版本号

 @return currentVersion
 */
+ (NSString *_Nonnull)currentVersion;


/**
 @brief 初始化UCloudRtcEngine
 @param userId 当前用户的ID
 @param appId 分配得到的应用ID
 @param roomId 即将加入的房间ID
 @param appKey 分配得到的appkey
 @param token  生成的token
 @return UCloudRtcEngine
 */
- (instancetype _Nonnull )initWithUserId:(NSString *_Nonnull)userId appId:(NSString *_Nonnull)appId roomId:(NSString *_Nonnull)roomId appKey:(NSString *_Nullable)appKey token:(NSString *_Nullable)token;

/**
@brief 初始化UCloudRtcEngine
@param appId 分配得到的应用ID
@param appKey 分配得到的appkey
@return UCloudRtcEngine
*/
- (instancetype _Nonnull )initWithAppID:(NSString *_Nonnull)appId appKey:(NSString *_Nullable)appKey completionBlock:(void (^_Nonnull)(int errorCode))completion;


/**
 @brief 加入房间

 @param completion completion
 */
- (void)joinRoomWithcompletionHandler:(void (^_Nonnull)(NSData * _Nonnull data, NSURLResponse * _Nonnull response, NSError * _Nonnull error))completion;


/**
@brief 加入房间
 
@param roomId 即将加入的房间ID
@param userId 当前用户的ID
@param token  生成的token
@param completion completion
*/
- (void)joinRoomWithRoomId:(NSString *_Nonnull)roomId userId:(NSString *_Nonnull)userId token:(NSString *_Nullable)token completionHandler:(void (^_Nonnull)(NSDictionary * _Nonnull response,int errorCode))completion;


/**
 @brief 退出房间
 */
- (void)leaveRoom;

/**
 @brief 手动发布
 */
- (void)publish;

/**
 @brief 取消发布
 */
- (void)unPublish;

/**
 @brief 手动订阅

 @param stream 将要订阅的流 <UCloudRtcStream *>
 */
- (void)subscribeMethod:(UCloudRtcStream *_Nonnull)stream;


/**
 @brief 取消订阅

 @param stream 将要取消订阅的流 <UCloudRtcStream *>
 */
- (void)unSubscribeMethod:(UCloudRtcStream *_Nonnull)stream;


/**
 @brief 设置本地的预览画面

 @param preview 本地画面即将渲染到的目标视图
 */
- (void)setLocalPreview:(UIView *_Nonnull)preview;


/**
 @brief 设置本地预览视频视图的模式

 @param previewMode 本地画面渲染模式
 */
- (void)setPreviewMode:(UCloudRtcVideoViewMode)previewMode;

/**
 @brief 设置远程视频视图的模式

 @param remoteViewMode 远程画面渲染模式
 */
- (void)setRemoteViewMode:(UCloudRtcVideoViewMode)remoteViewMode;


/**
 @brief 切换本地摄像头
 */
- (void)switchCamera;


/**
 @brief 设置本地流是否静音

 @param isMute 是否禁用
 */
- (void)setMute:(BOOL)isMute;


/**
 @brief 设置本地流是否禁用视频

 @param isOpen 是否开启
 */
- (void)openCamera:(BOOL)isOpen;


/**
 @brief 开启免提

 @param isOpen 是否开启
 */
- (void)openLoudspeaker:(BOOL)isOpen;


/**
 @brief 设置远程流是否禁用视频

 @param stream 目标远端流
 @param isMute 是否禁用视频
 */
- (void)setRemoteStream:(UCloudRtcStream *_Nonnull)stream muteVideo:(BOOL)isMute;


/**
 @brief 设置远程流是否禁用音频

 @param stream 目标远端流
 @param isMute 是否禁用音频频
 */
- (void)setRemoteStream:(UCloudRtcStream *_Nonnull)stream muteAudio:(BOOL)isMute;


/**
 @brief 开始视频录制

 */
- (void)startRecord:(UCloudRtcRecordConfig *_Nonnull)recordConfig;

/**
 @brief 停止视频录制
 
 */
- (void)stopRecord;

/**
@brief 开始本地录制
 
@param recordConfig 本地录制参数配置
*/
- (void)startNativeRecord:(NSDictionary *_Nonnull)recordConfig;

/**
@brief 停止本地录制

*/
- (void)stopNativeRecord;




/**
@brief 网络音频播放
 
@param path 文件路径
@param repeat 是否循环播放
*/
- (void)startMediaPlay:(NSString *_Nonnull)path repeat:(BOOL)repeat;


/**
@brief 停止网络音频播放
*/
- (void)stopMediaPlay;

/**
@brief 暂停网络音频播放
*/
- (void)pauseMediaPlay;


/**
@brief 恢复网络音频播放
*/
- (void)resumeMediaPlay;

/**
@brief 获取音效文件播放音量
 
@return 音效文件播放音量
*/
- (double)getMediaVolume;

/**
@brief 设置音效文件播放音量
 
@param volume 音效文件播放音量
@return 设置结果
*/
- (int)setMediaVolume:(double)volume;

/**
@brief 发送自定义消息
 
@param customCommand 自定义消息内容
*/
- (void)sendCustomCommand:(NSString *_Nonnull)customCommand;
@end
