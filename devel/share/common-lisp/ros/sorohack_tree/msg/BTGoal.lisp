; Auto-generated. Do not edit!


(cl:in-package sorohack_tree-msg)


;//! \htmlinclude BTGoal.msg.html

(cl:defclass <BTGoal> (roslisp-msg-protocol:ros-message)
  ((bt_action_goal
    :reader bt_action_goal
    :initarg :bt_action_goal
    :type cl:string
    :initform ""))
)

(cl:defclass BTGoal (<BTGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BTGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BTGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name sorohack_tree-msg:<BTGoal> is deprecated: use sorohack_tree-msg:BTGoal instead.")))

(cl:ensure-generic-function 'bt_action_goal-val :lambda-list '(m))
(cl:defmethod bt_action_goal-val ((m <BTGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sorohack_tree-msg:bt_action_goal-val is deprecated.  Use sorohack_tree-msg:bt_action_goal instead.")
  (bt_action_goal m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BTGoal>) ostream)
  "Serializes a message object of type '<BTGoal>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'bt_action_goal))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'bt_action_goal))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BTGoal>) istream)
  "Deserializes a message object of type '<BTGoal>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'bt_action_goal) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'bt_action_goal) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BTGoal>)))
  "Returns string type for a message object of type '<BTGoal>"
  "sorohack_tree/BTGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BTGoal)))
  "Returns string type for a message object of type 'BTGoal"
  "sorohack_tree/BTGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BTGoal>)))
  "Returns md5sum for a message object of type '<BTGoal>"
  "089d672a9a4e6b26982ebad40e0104ea")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BTGoal)))
  "Returns md5sum for a message object of type 'BTGoal"
  "089d672a9a4e6b26982ebad40e0104ea")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BTGoal>)))
  "Returns full string definition for message of type '<BTGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# goal of the action, since this is a general action, a string is ok~%string bt_action_goal~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BTGoal)))
  "Returns full string definition for message of type 'BTGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# goal of the action, since this is a general action, a string is ok~%string bt_action_goal~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BTGoal>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'bt_action_goal))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BTGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'BTGoal
    (cl:cons ':bt_action_goal (bt_action_goal msg))
))
